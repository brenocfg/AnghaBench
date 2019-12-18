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
 int /*<<< orphan*/  alarmtimer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanuppeer () ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connected ; 
 int /*<<< orphan*/ * cout ; 
 int data ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ proxflag ; 
 int /*<<< orphan*/  pswitch (int) ; 
 int /*<<< orphan*/  shutdown (int,int) ; 

void
lostpeer(int dummy)
{
	int oerrno = errno;

	alarmtimer(0);
	if (connected) {
		if (cout != NULL) {
			(void)shutdown(fileno(cout), 1+1);
			(void)fclose(cout);
			cout = NULL;
		}
		if (data >= 0) {
			(void)shutdown(data, 1+1);
			(void)close(data);
			data = -1;
		}
		connected = 0;
	}
	pswitch(1);
	if (connected) {
		if (cout != NULL) {
			(void)shutdown(fileno(cout), 1+1);
			(void)fclose(cout);
			cout = NULL;
		}
		connected = 0;
	}
	proxflag = 0;
	pswitch(0);
	cleanuppeer();
	errno = oerrno;
}