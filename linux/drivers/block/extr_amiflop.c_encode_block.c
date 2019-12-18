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
 int /*<<< orphan*/  encode (unsigned long,unsigned long*) ; 

__attribute__((used)) static void encode_block(unsigned long *dest, unsigned long *src, int len)
{
	int cnt, to_cnt = 0;
	unsigned long data;

	/* odd bits */
	for (cnt = 0; cnt < len / 4; cnt++) {
		data = src[cnt] >> 1;
		encode(data, dest + to_cnt++);
	}

	/* even bits */
	for (cnt = 0; cnt < len / 4; cnt++) {
		data = src[cnt];
		encode(data, dest + to_cnt++);
	}
}