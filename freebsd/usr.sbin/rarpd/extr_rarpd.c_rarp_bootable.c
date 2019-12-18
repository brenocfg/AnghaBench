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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int in_addr_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ntohl (int) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  pidfile_fh ; 
 int /*<<< orphan*/  pidfile_remove (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tftp_dir ; 

__attribute__((used)) static int
rarp_bootable(in_addr_t addr)
{
	struct dirent *dent;
	DIR *d;
	char ipname[9];
	static DIR *dd = NULL;

	(void)sprintf(ipname, "%08X", (in_addr_t)ntohl(addr));

	/*
	 * If directory is already open, rewind it.  Otherwise, open it.
	 */
	if ((d = dd) != NULL)
		rewinddir(d);
	else {
		if (chdir(tftp_dir) == -1) {
			logmsg(LOG_ERR, "chdir: %s: %m", tftp_dir);
			goto rarp_bootable_err;
		}
		d = opendir(".");
		if (d == NULL) {
			logmsg(LOG_ERR, "opendir: %m");
			goto rarp_bootable_err;
		}
		dd = d;
	}
	while ((dent = readdir(d)) != NULL)
		if (strncmp(dent->d_name, ipname, 8) == 0)
			return 1;
	return 0;

rarp_bootable_err:
	pidfile_remove(pidfile_fh);
	exit(1);
}