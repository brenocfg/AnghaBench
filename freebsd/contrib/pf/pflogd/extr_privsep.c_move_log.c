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
typedef  int /*<<< orphan*/  ren ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int PATH_MAX ; 
 int arc4random () ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,...) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rename (char const*,char*) ; 
 int snprintf (char*,int,char*,char const*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int
move_log(const char *name)
{
	char ren[PATH_MAX];
	int len;

	for (;;) {
		int fd;

		len = snprintf(ren, sizeof(ren), "%s.bad.%08x",
		    name, arc4random());
		if (len >= sizeof(ren)) {
			logmsg(LOG_ERR, "[priv] new name too long");
			return (1);
		}

		/* lock destinanion */
		fd = open(ren, O_CREAT|O_EXCL, 0);
		if (fd >= 0) {
			close(fd);
			break;
		}
		/* if file exists, try another name */
		if (errno != EEXIST && errno != EINTR) {
			logmsg(LOG_ERR, "[priv] failed to create new name: %s",
			    strerror(errno));
			return (1);			
		}
	}

	if (rename(name, ren)) {
		logmsg(LOG_ERR, "[priv] failed to rename %s to %s: %s",
		    name, ren, strerror(errno));
		return (1);
	}

	logmsg(LOG_NOTICE,
	       "[priv]: log file %s moved to %s", name, ren);

	return (0);
}