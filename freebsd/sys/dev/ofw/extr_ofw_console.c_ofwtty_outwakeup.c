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

/* Variables and functions */
 int OFBURSTLEN ; 
 int /*<<< orphan*/  OF_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stdout ; 
 int ttydisc_getc (struct tty*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ofwtty_outwakeup(struct tty *tp)
{
	int len;
	u_char buf[OFBURSTLEN];

	for (;;) {
		len = ttydisc_getc(tp, buf, sizeof buf);
		if (len == 0)
			break;
		OF_write(stdout, buf, len);
	}
}