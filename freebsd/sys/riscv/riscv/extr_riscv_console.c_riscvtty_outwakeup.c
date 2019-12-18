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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAX_BURST_LEN ; 
 int /*<<< orphan*/  riscv_putc (int /*<<< orphan*/ ) ; 
 int ttydisc_getc (struct tty*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
riscvtty_outwakeup(struct tty *tp)
{
	u_char buf[MAX_BURST_LEN];
	int len;
	int i;

	for (;;) {
		len = ttydisc_getc(tp, buf, sizeof(buf));
		if (len == 0)
			break;

		KASSERT(len == 1, ("tty error"));

		for (i = 0; i < len; i++)
			riscv_putc(buf[i]);
	}
}