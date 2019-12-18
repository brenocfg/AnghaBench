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
struct termios {int dummy; } ;
typedef  int /*<<< orphan*/  sig_t ;
struct TYPE_2__ {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAUDRATE ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  HUPCL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TCIOFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  VERBOSE ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int expect (char*) ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  tcflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 TYPE_1__ term ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vawrite (char*,int) ; 

int
v3451_dialer(char *num, char *acu)
{
	sig_t func;
	int ok;
	int slow = number(value(BAUDRATE)) < 1200;
	char phone[50];
	struct termios cntrl;

	/*
	 * Get in synch
	 */
	vawrite("I\r", 1 + slow);
	vawrite("I\r", 1 + slow);
	vawrite("I\r", 1 + slow);
	vawrite("\005\r", 2 + slow);
	if (!expect("READY")) {
		printf("can't synchronize with vadic 3451\n");
#ifdef ACULOG
		logent(value(HOST), num, "vadic", "can't synch up");
#endif
		return (0);
	}
	tcgetattr(FD, &cntrl);
	term.c_cflag |= HUPCL;
	tcsetattr(FD, TCSANOW, &cntrl);
	sleep(1);
	vawrite("D\r", 2 + slow);
	if (!expect("NUMBER?")) {
		printf("Vadic will not accept dial command\n");
#ifdef ACULOG
		logent(value(HOST), num, "vadic", "will not accept dial");
#endif
		return (0);
	}
	(void)snprintf(phone, sizeof phone, "%s\r", num);
	vawrite(phone, 1 + slow);
	if (!expect(phone)) {
		printf("Vadic will not accept phone number\n");
#ifdef ACULOG
		logent(value(HOST), num, "vadic", "will not accept number");
#endif
		return (0);
	}
	func = signal(SIGINT,SIG_IGN);
	/*
	 * You cannot interrupt the Vadic when its dialing;
	 * even dropping DTR does not work (definitely a
	 * brain damaged design).
	 */
	vawrite("\r", 1 + slow);
	vawrite("\r", 1 + slow);
	if (!expect("DIALING:")) {
		printf("Vadic failed to dial\n");
#ifdef ACULOG
		logent(value(HOST), num, "vadic", "failed to dial");
#endif
		return (0);
	}
	if (boolean(value(VERBOSE)))
		printf("\ndialing...");
	ok = expect("ON LINE");
	signal(SIGINT, func);
	if (!ok) {
		printf("call failed\n");
#ifdef ACULOG
		logent(value(HOST), num, "vadic", "call failed");
#endif
		return (0);
	}
	tcflush(FD, TCIOFLUSH);
	return (1);
}