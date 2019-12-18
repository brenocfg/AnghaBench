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

/* Variables and functions */
 int /*<<< orphan*/  FIOASYNC ; 
 int /*<<< orphan*/  FIONBIO ; 
 scalar_t__ IS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ OS ; 
 scalar_t__ SP ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  cfmakeraw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfsetispeed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfsetospeed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setchars () ; 
 int /*<<< orphan*/  speed (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmode ; 
 int /*<<< orphan*/  ttyn ; 

__attribute__((used)) static void
setttymode(int raw)
{
	int off = 0;

	(void)tcflush(STDIN_FILENO, TCIOFLUSH);	/* clear out the crap */
	ioctl(STDIN_FILENO, FIONBIO, &off);	/* turn off non-blocking mode */
	ioctl(STDIN_FILENO, FIOASYNC, &off);	/* ditto for async mode */

	if (IS)
		cfsetispeed(&tmode, speed(IS));
	else if (SP)
		cfsetispeed(&tmode, speed(SP));
	if (OS)
		cfsetospeed(&tmode, speed(OS));
	else if (SP)
		cfsetospeed(&tmode, speed(SP));
	set_flags(0);
	setchars();
	if (raw)
		cfmakeraw(&tmode);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &tmode) < 0) {
		syslog(LOG_ERR, "tcsetattr %s: %m", ttyn);
		exit(1);
	}
}