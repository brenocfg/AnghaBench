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
 unsigned char CISTPL_END ; 
 void** gayle_attribute ; 

int pcmcia_copy_tuple(unsigned char tuple_id, void *tuple, int max_len)
{
	unsigned char id, *dest;
	int cnt, pos, len;

	dest = tuple;
	pos = 0;

	id = gayle_attribute[pos];

	while((id != CISTPL_END) && (pos < 0x10000)) {
		len = (int)gayle_attribute[pos+2] + 2;
		if (id == tuple_id) {
			len = (len > max_len)?max_len:len;
			for (cnt = 0; cnt < len; cnt++) {
				*dest++ = gayle_attribute[pos+(cnt<<1)];
			}

			return len;
		}
		pos += len<<1;
		id = gayle_attribute[pos];
	}

	return 0;
}