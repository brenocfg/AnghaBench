#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int tr_sendrecv ;
typedef  int /*<<< orphan*/  thishost ;
struct printer {char* stat_send; char* stat_recv; char* lp; char* tr_timestr; char* printer; char* jobnum; int /*<<< orphan*/  jobdfnum; int /*<<< orphan*/  tr_start; int /*<<< orphan*/  tr_done; } ;

/* Variables and functions */
 double DIFFTIME_TS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXHOSTNAMELEN ; 
 int O_APPEND ; 
 int O_WRONLY ; 
 int STATLINE_SIZE ; 
#define  TR_PRINTING 130 
#define  TR_RECVING 129 
#define  TR_SENDING 128 
 int /*<<< orphan*/  UPD_EOSTAT (char*) ; 
 char* _PATH_DEFDEVLP ; 
 int /*<<< orphan*/  close (int) ; 
 char* from_ip ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  lpd_gettime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void
trstat_write(struct printer *pp, tr_sendrecv sendrecv, size_t bytecnt,
    const char *userid, const char *otherhost, const char *orighost)
{
#define STATLINE_SIZE 1024
	double trtime;
	size_t remspace;
	int statfile;
	char thishost[MAXHOSTNAMELEN], statline[STATLINE_SIZE];
	char *eostat;
	const char *lprhost, *recvdev, *recvhost, *rectype;
	const char *sendhost, *statfname;
#define UPD_EOSTAT(xStr) do {         \
	eostat = strchr(xStr, '\0');  \
	remspace = eostat - xStr;     \
} while(0)

	lpd_gettime(&pp->tr_done, NULL, (size_t)0);
	trtime = DIFFTIME_TS(pp->tr_done, pp->tr_start);

	gethostname(thishost, sizeof(thishost));
	lprhost = sendhost = recvhost = recvdev = NULL;
	switch (sendrecv) {
	    case TR_SENDING:
		rectype = "send";
		statfname = pp->stat_send;
		sendhost = thishost;
		recvhost = otherhost;
		break;
	    case TR_RECVING:
		rectype = "recv";
		statfname = pp->stat_recv;
		sendhost = otherhost;
		recvhost = thishost;
		break;
	    case TR_PRINTING:
		/*
		 * This case is for copying to a device (presumably local,
		 * though filters using things like 'net/CAP' can confuse
		 * this assumption...).
		 */
		rectype = "prnt";
		statfname = pp->stat_send;
		sendhost = thishost;
		recvdev = _PATH_DEFDEVLP;
		if (pp->lp) recvdev = pp->lp;
		break;
	    default:
		/* internal error...  should we syslog/printf an error? */
		return;
	}
	if (statfname == NULL)
		return;

	/*
	 * the original-host and userid are found out by reading thru the
	 * cf (control-file) for the job.  Unfortunately, on incoming jobs
	 * the df's (data-files) are sent before the matching cf, so the
	 * orighost & userid are generally not-available for incoming jobs.
	 *
	 * (it would be nice to create a work-around for that..)
	 */
	if (orighost && (*orighost != '\0'))
		lprhost = orighost;
	else
		lprhost = ".na.";
	if (*userid == '\0')
		userid = NULL;

	/*
	 * Format of statline.
	 * Some of the keywords listed here are not implemented here, but
	 * they are listed to reserve the meaning for a given keyword.
	 * Fields are separated by a blank.  The fields in statline are:
	 *   <tstamp>      - time the transfer started
	 *   <ptrqueue>    - name of the printer queue (the short-name...)
	 *   <hname>       - hostname the file originally came from (the
	 *		     'lpr host'), if known, or  "_na_" if not known.
	 *   <xxx>         - id of job from that host (generally three digits)
	 *   <n>           - file count (# of file within job)
	 *   <rectype>     - 4-byte field indicating the type of transfer
	 *		     statistics record.  "send" means it's from the
	 *		     host sending a datafile, "recv" means it's from
	 *		     a host as it receives a datafile.
	 *   user=<userid> - user who sent the job (if known)
	 *   secs=<n>      - seconds it took to transfer the file
	 *   bytes=<n>     - number of bytes transferred (ie, "bytecount")
	 *   bps=<n.n>e<n> - Bytes/sec (if the transfer was "big enough"
	 *		     for this to be useful)
	 * ! top=<str>     - type of printer (if the type is defined in
	 *		     printcap, and if this statline is for sending
	 *		     a file to that ptr)
	 * ! qls=<n>       - queue-length at start of send/print-ing a job
	 * ! qle=<n>       - queue-length at end of send/print-ing a job
	 *   sip=<addr>    - IP address of sending host, only included when
	 *		     receiving a job.
	 *   shost=<hname> - sending host (if that does != the original host)
	 *   rhost=<hname> - hostname receiving the file (ie, "destination")
	 *   rdev=<dev>    - device receiving the file, when the file is being
	 *		     send to a device instead of a remote host.
	 *
	 * Note: A single print job may be transferred multiple times.  The
	 * original 'lpr' occurs on one host, and that original host might
	 * send to some interim host (or print server).  That interim host
	 * might turn around and send the job to yet another host (most likely
	 * the real printer).  The 'shost=' parameter is only included if the
	 * sending host for this particular transfer is NOT the same as the
	 * host which did the original 'lpr'.
	 *
	 * Many values have 'something=' tags before them, because they are
	 * in some sense "optional", or their order may vary.  "Optional" may
	 * mean in the sense that different SITES might choose to have other
	 * fields in the record, or that some fields are only included under
	 * some circumstances.  Programs processing these records should not
	 * assume the order or existence of any of these keyword fields.
	 */
	snprintf(statline, STATLINE_SIZE, "%s %s %s %s %03ld %s",
	    pp->tr_timestr, pp->printer, lprhost, pp->jobnum,
	    pp->jobdfnum, rectype);
	UPD_EOSTAT(statline);

	if (userid != NULL) {
		snprintf(eostat, remspace, " user=%s", userid);
		UPD_EOSTAT(statline);
	}
	snprintf(eostat, remspace, " secs=%#.2f bytes=%lu", trtime,
	    (unsigned long)bytecnt);
	UPD_EOSTAT(statline);

	/*
	 * The bps field duplicates info from bytes and secs, so do
	 * not bother to include it for very small files.
	 */
	if ((bytecnt > 25000) && (trtime > 1.1)) {
		snprintf(eostat, remspace, " bps=%#.2e",
		    ((double)bytecnt/trtime));
		UPD_EOSTAT(statline);
	}

	if (sendrecv == TR_RECVING) {
		if (remspace > 5+strlen(from_ip) ) {
			snprintf(eostat, remspace, " sip=%s", from_ip);
			UPD_EOSTAT(statline);
		}
	}
	if (0 != strcmp(lprhost, sendhost)) {
		if (remspace > 7+strlen(sendhost) ) {
			snprintf(eostat, remspace, " shost=%s", sendhost);
			UPD_EOSTAT(statline);
		}
	}
	if (recvhost) {
		if (remspace > 7+strlen(recvhost) ) {
			snprintf(eostat, remspace, " rhost=%s", recvhost);
			UPD_EOSTAT(statline);
		}
	}
	if (recvdev) {
		if (remspace > 6+strlen(recvdev) ) {
			snprintf(eostat, remspace, " rdev=%s", recvdev);
			UPD_EOSTAT(statline);
		}
	}
	if (remspace > 1) {
		strcpy(eostat, "\n");
	} else {
		/* probably should back up to just before the final " x=".. */
		strcpy(statline+STATLINE_SIZE-2, "\n");
	}
	statfile = open(statfname, O_WRONLY|O_APPEND, 0664);
	if (statfile < 0) {
		/* statfile was given, but we can't open it.  should we
		 * syslog/printf this as an error? */
		return;
	}
	write(statfile, statline, strlen(statline));
	close(statfile);

	return;
#undef UPD_EOSTAT
}