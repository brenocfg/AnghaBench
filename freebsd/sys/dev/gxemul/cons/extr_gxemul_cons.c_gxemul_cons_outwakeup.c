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
typedef  int /*<<< orphan*/  u_char ;
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  ch ;

/* Variables and functions */
 int /*<<< orphan*/  GC_LOCK () ; 
 int /*<<< orphan*/  GC_UNLOCK () ; 
 int /*<<< orphan*/  gxemul_cons_write (int /*<<< orphan*/ ) ; 
 int ttydisc_getc (struct tty*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
gxemul_cons_outwakeup(struct tty *tp)
{
	int len;
	u_char ch;

	/*
	 * XXXRW: Would be nice not to do blocking writes to the console here,
	 * rescheduling on our timer tick if work remains to be done..
	 */
	for (;;) {
		len = ttydisc_getc(tp, &ch, sizeof(ch));
		if (len == 0)
			break;
		GC_LOCK();
		gxemul_cons_write(ch);
		GC_UNLOCK();
	}
}