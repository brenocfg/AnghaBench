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
struct tty {int dummy; } ;

/* Variables and functions */
 scalar_t__ ttydisc_can_bypass (struct tty*) ; 
 scalar_t__ ttydisc_rint (struct tty*,char const,int /*<<< orphan*/ ) ; 
 size_t ttydisc_rint_bypass (struct tty*,void const*,size_t) ; 

size_t
ttydisc_rint_simple(struct tty *tp, const void *buf, size_t len)
{
	const char *cbuf;

	if (ttydisc_can_bypass(tp))
		return (ttydisc_rint_bypass(tp, buf, len));

	for (cbuf = buf; len-- > 0; cbuf++) {
		if (ttydisc_rint(tp, *cbuf, 0) != 0)
			break;
	}

	return (cbuf - (const char *)buf);
}