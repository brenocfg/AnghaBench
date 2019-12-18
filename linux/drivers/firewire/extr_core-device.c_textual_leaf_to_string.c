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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 unsigned int min (int const,unsigned int) ; 

__attribute__((used)) static int textual_leaf_to_string(const u32 *block, char *buf, size_t size)
{
	unsigned int quadlets, i;
	char c;

	if (!size || !buf)
		return -EINVAL;

	quadlets = min(block[0] >> 16, 256U);
	if (quadlets < 2)
		return -ENODATA;

	if (block[1] != 0 || block[2] != 0)
		/* unknown language/character set */
		return -ENODATA;

	block += 3;
	quadlets -= 2;
	for (i = 0; i < quadlets * 4 && i < size - 1; i++) {
		c = block[i / 4] >> (24 - 8 * (i % 4));
		if (c == '\0')
			break;
		buf[i] = c;
	}
	buf[i] = '\0';

	return i;
}