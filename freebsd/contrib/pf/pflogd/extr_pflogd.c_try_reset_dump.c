#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
struct pcap_file_header {int /*<<< orphan*/  linktype; scalar_t__ sigfigs; int /*<<< orphan*/  snaplen; int /*<<< orphan*/  thiszone; int /*<<< orphan*/  version_minor; int /*<<< orphan*/  version_major; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_2__ {int /*<<< orphan*/  linktype; int /*<<< orphan*/  snapshot; int /*<<< orphan*/  tzoff; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PCAP_VERSION_MAJOR ; 
 int /*<<< orphan*/  PCAP_VERSION_MINOR ; 
 int /*<<< orphan*/  TCPDUMP_MAGIC ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ cur_snaplen ; 
 int /*<<< orphan*/ * dpcap ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_buffer (int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* hpcap ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ priv_move_log () ; 
 int priv_open_log () ; 
 scalar_t__ scan_dump (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ set_snaplen (scalar_t__) ; 
 int /*<<< orphan*/  set_suspended (int /*<<< orphan*/ ) ; 
 scalar_t__ setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snaplen ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
try_reset_dump(int nomove)
{
	struct pcap_file_header hdr;
	struct stat st;
	int fd;
	FILE *fp;

	if (hpcap == NULL)
		return (-1);

	if (dpcap) {
		flush_buffer(dpcap);
		fclose(dpcap);
		dpcap = NULL;
	}

	/*
	 * Basically reimplement pcap_dump_open() because it truncates
	 * files and duplicates headers and such.
	 */
	fd = priv_open_log();
	if (fd < 0)
		return (-1);

	fp = fdopen(fd, "a+");

	if (fp == NULL) {
		logmsg(LOG_ERR, "Error: %s: %s", filename, strerror(errno));
		close(fd);
		return (-1);
	}
	if (fstat(fileno(fp), &st) == -1) {
		logmsg(LOG_ERR, "Error: %s: %s", filename, strerror(errno));
		fclose(fp);
		return (-1);
	}

	/* set FILE unbuffered, we do our own buffering */
	if (setvbuf(fp, NULL, _IONBF, 0)) {
		logmsg(LOG_ERR, "Failed to set output buffers");
		fclose(fp);
		return (-1);
	}

#define TCPDUMP_MAGIC 0xa1b2c3d4

	if (st.st_size == 0) {
		if (snaplen != cur_snaplen) {
			logmsg(LOG_NOTICE, "Using snaplen %d", snaplen);
			if (set_snaplen(snaplen))
				logmsg(LOG_WARNING,
				    "Failed, using old settings");
		}
		hdr.magic = TCPDUMP_MAGIC;
		hdr.version_major = PCAP_VERSION_MAJOR;
		hdr.version_minor = PCAP_VERSION_MINOR;
		hdr.thiszone = hpcap->tzoff;
		hdr.snaplen = hpcap->snapshot;
		hdr.sigfigs = 0;
		hdr.linktype = hpcap->linktype;

		if (fwrite((char *)&hdr, sizeof(hdr), 1, fp) != 1) {
			fclose(fp);
			return (-1);
		}
	} else if (scan_dump(fp, st.st_size)) {
		fclose(fp);
		if (nomove || priv_move_log()) {
			logmsg(LOG_ERR,
			    "Invalid/incompatible log file, move it away");
			return (-1);
		}
		return (1);
	}

	dpcap = fp;

	set_suspended(0);
	flush_buffer(fp);

	return (0);
}