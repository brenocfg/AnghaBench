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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  STEP ; 

void
swab(const void * __restrict from, void * __restrict to, ssize_t len)
{
	unsigned long temp;
	int n;
	char *fp, *tp;

	if (len <= 0)
		return;
	n = len >> 1;
	fp = (char *)from;
	tp = (char *)to;
#define	STEP	temp = *fp++,*tp++ = *fp++,*tp++ = temp
	/* round to multiple of 8 */
	for (; n & 0x7; --n)
		STEP;
	for (n >>= 3; n > 0; --n) {
		STEP; STEP; STEP; STEP;
		STEP; STEP; STEP; STEP;
	}
}