#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int8_t ;
struct TYPE_11__ {size_t rmp_flnmsize; char rmp_flnm; void* rmp_retcode; void* rmp_version; void* rmp_session; int /*<<< orphan*/  rmp_seqno; int /*<<< orphan*/  rmp_type; } ;
struct TYPE_10__ {size_t rmp_flnmsize; char rmp_flnm; int /*<<< orphan*/  rmp_seqno; } ;
struct rmp_packet {TYPE_2__ r_brpl; TYPE_1__ r_brq; } ;
struct TYPE_12__ {int /*<<< orphan*/  rmplen; int /*<<< orphan*/  bootfd; struct rmp_packet rmp; } ;
typedef  TYPE_3__ RMPCONN ;

/* Variables and functions */
 int /*<<< orphan*/  COPYWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t C_MAXFILE ; 
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EnetStr (TYPE_3__*) ; 
 TYPE_3__* FindConn (TYPE_3__*) ; 
 int /*<<< orphan*/  GenSessID () ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RMPBOOTDATA ; 
 int /*<<< orphan*/  RMPBOOTSIZE (size_t) ; 
 int /*<<< orphan*/  RMP_BOOT_REPL ; 
 void* RMP_E_BUSY ; 
 void* RMP_E_NOFILE ; 
 void* RMP_E_OKAY ; 
 void* RMP_E_OPENFILE ; 
 int /*<<< orphan*/  RMP_VERSION ; 
 int /*<<< orphan*/  RemoveConn (TYPE_3__*) ; 
 scalar_t__ STREQN (char*,char*) ; 
 int SendPacket (TYPE_3__*) ; 
 scalar_t__ errno ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int
SendBootRepl(struct rmp_packet *req, RMPCONN *rconn, char *filelist[])
{
	int retval;
	char *filename, filepath[RMPBOOTDATA+1];
	RMPCONN *oldconn;
	struct rmp_packet *rpl;
	char *src, *dst1, *dst2;
	u_int8_t i;

	/*
	 *  If another connection already exists, delete it since we
	 *  are obviously starting again.
	 */
	if ((oldconn = FindConn(rconn)) != NULL) {
		syslog(LOG_WARNING, "%s: dropping existing connection",
		       EnetStr(oldconn));
		RemoveConn(oldconn);
	}

	rpl = &rconn->rmp;			/* cache ptr to RMP packet */

	/*
	 *  Set up assorted fields in reply packet.
	 */
	rpl->r_brpl.rmp_type = RMP_BOOT_REPL;
	COPYWORD(req->r_brq.rmp_seqno, rpl->r_brpl.rmp_seqno);
	rpl->r_brpl.rmp_session = htons(GenSessID());
	rpl->r_brpl.rmp_version = htons(RMP_VERSION);
	rpl->r_brpl.rmp_flnmsize = req->r_brq.rmp_flnmsize;

	/*
	 *  Copy file name to `filepath' string, and into reply packet.
	 */
	src = &req->r_brq.rmp_flnm;
	dst1 = filepath;
	dst2 = &rpl->r_brpl.rmp_flnm;
	for (i = 0; i < req->r_brq.rmp_flnmsize; i++)
		*dst1++ = *dst2++ = *src++;
	*dst1 = '\0';

	/*
	 *  If we are booting HP-UX machines, their secondary loader will
	 *  ask for files like "/hp-ux".  As a security measure, we do not
	 *  allow boot files to lay outside the boot directory (unless they
	 *  are purposely link'd out.  So, make `filename' become the path-
	 *  stripped file name and spoof the client into thinking that it
	 *  really got what it wanted.
	 */
	filename = (filename = strrchr(filepath,'/'))? ++filename: filepath;

	/*
	 *  Check that this is a valid boot file name.
	 */
	for (i = 0; i < C_MAXFILE && filelist[i] != NULL; i++)
		if (STREQN(filename, filelist[i]))
			goto match;

	/*
	 *  Invalid boot file name, set error and send reply packet.
	 */
	rpl->r_brpl.rmp_retcode = RMP_E_NOFILE;
	retval = 0;
	goto sendpkt;

match:
	/*
	 *  This is a valid boot file.  Open the file and save the file
	 *  descriptor associated with this connection and set success
	 *  indication.  If the file couldnt be opened, set error:
	 *  	"no such file or dir" - RMP_E_NOFILE
	 *	"file table overflow" - RMP_E_BUSY
	 *	"too many open files" - RMP_E_BUSY
	 *	anything else         - RMP_E_OPENFILE
	 */
	if ((rconn->bootfd = open(filename, O_RDONLY, 0600)) < 0) {
		rpl->r_brpl.rmp_retcode = (errno == ENOENT)? RMP_E_NOFILE:
			(errno == EMFILE || errno == ENFILE)? RMP_E_BUSY:
			RMP_E_OPENFILE;
		retval = 0;
	} else {
		rpl->r_brpl.rmp_retcode = RMP_E_OKAY;
		retval = 1;
	}

sendpkt:
	syslog(LOG_INFO, "%s: request to boot %s (%s)",
	       EnetStr(rconn), filename, retval? "granted": "denied");

	rconn->rmplen = RMPBOOTSIZE(rpl->r_brpl.rmp_flnmsize);

	return (retval & SendPacket(rconn));
}