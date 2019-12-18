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
 unsigned int badoff ; 
 void** good_buf ; 
 scalar_t__ memcmp (void**,void**,unsigned int) ; 
 int /*<<< orphan*/  prt (char*,...) ; 
 int /*<<< orphan*/  report_failure (int) ; 
 unsigned int short_at (void**) ; 
 void** temp_buf ; 

void
check_buffers(unsigned offset, unsigned size)
{
	unsigned char c, t;
	unsigned i = 0;
	unsigned n = 0;
	unsigned op = 0;
	unsigned bad = 0;

	if (memcmp(good_buf + offset, temp_buf, size) != 0) {
		prt("READ BAD DATA: offset = 0x%x, size = 0x%x\n",
		    offset, size);
		prt("OFFSET\tGOOD\tBAD\tRANGE\n");
		while (size > 0) {
			c = good_buf[offset];
			t = temp_buf[i];
			if (c != t) {
				if (n == 0) {
					bad = short_at(&temp_buf[i]);
					prt("0x%5x\t0x%04x\t0x%04x", offset,
					    short_at(&good_buf[offset]), bad);
					op = temp_buf[offset & 1 ? i+1 : i];
				}
				n++;
				badoff = offset;
			}
			offset++;
			i++;
			size--;
		}
		if (n) {
			prt("\t0x%5x\n", n);
			if (bad)
				prt("operation# (mod 256) for the bad data may be %u\n", ((unsigned)op & 0xff));
			else
				prt("operation# (mod 256) for the bad data unknown, check HOLE and EXTEND ops\n");
		} else
			prt("????????????????\n");
		report_failure(110);
	}
}