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
struct termios {int dummy; } ;
struct printer {scalar_t__ mode_set; int /*<<< orphan*/  printer; int /*<<< orphan*/  baud_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TIOCEXCL ; 
 int /*<<< orphan*/  cfsetspeed (struct termios*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msearch (char*,struct termios*) ; 
 int /*<<< orphan*/  pfd ; 
 char* strdup (scalar_t__) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void
setty(const struct printer *pp)
{
	struct termios ttybuf;

	if (ioctl(pfd, TIOCEXCL, (char *)0) < 0) {
		syslog(LOG_ERR, "%s: ioctl(TIOCEXCL): %m", pp->printer);
		exit(1);
	}
	if (tcgetattr(pfd, &ttybuf) < 0) {
		syslog(LOG_ERR, "%s: tcgetattr: %m", pp->printer);
		exit(1);
	}
	if (pp->baud_rate > 0)
		cfsetspeed(&ttybuf, pp->baud_rate);
	if (pp->mode_set) {
		char *s = strdup(pp->mode_set), *tmp;

		while ((tmp = strsep(&s, ",")) != NULL) {
			(void) msearch(tmp, &ttybuf);
		}
	}
	if (pp->mode_set != 0 || pp->baud_rate > 0) {
		if (tcsetattr(pfd, TCSAFLUSH, &ttybuf) == -1) {
			syslog(LOG_ERR, "%s: tcsetattr: %m", pp->printer);
		}
	}
}