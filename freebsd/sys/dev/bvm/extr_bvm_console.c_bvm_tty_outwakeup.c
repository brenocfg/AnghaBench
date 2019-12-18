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
 int BVMBURSTLEN ; 
 int /*<<< orphan*/  bvm_wcons (int /*<<< orphan*/ ) ; 
 int ttydisc_getc (struct tty*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bvm_tty_outwakeup(struct tty *tp)
{
	int len, written;
	u_char buf[BVMBURSTLEN];

	for (;;) {
		len = ttydisc_getc(tp, buf, sizeof(buf));
		if (len == 0)
			break;

		written = 0;
		while (written < len)
			bvm_wcons(buf[written++]);
	}
}