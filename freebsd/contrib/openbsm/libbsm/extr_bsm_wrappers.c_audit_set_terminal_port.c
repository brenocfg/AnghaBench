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
struct stat {int st_rdev; } ;
typedef  int dev_t ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int NODEV ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 scalar_t__ errno ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int kAUBadParamErr ; 
 int kAUNoErr ; 
 int kAUStatErr ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
audit_set_terminal_port(dev_t *p)
{
	struct stat st;

	if (p == NULL)
		return (kAUBadParamErr);

#ifdef NODEV
	*p = NODEV;
#else
	*p = -1;
#endif

	/* for /usr/bin/login, try fstat() first */
	if (fstat(STDIN_FILENO, &st) != 0) {
		if (errno != EBADF) {
			syslog(LOG_ERR, "fstat() failed (%s)",
			    strerror(errno));
			return (kAUStatErr);
		}
		if (stat("/dev/console", &st) != 0) {
			syslog(LOG_ERR, "stat() failed (%s)",
			    strerror(errno));
			return (kAUStatErr);
		}
	}
	*p = st.st_rdev;
	return (kAUNoErr);
}