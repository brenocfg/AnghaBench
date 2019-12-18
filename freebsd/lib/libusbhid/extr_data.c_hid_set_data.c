#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_3__ {int report_ID; int pos; int report_size; } ;
typedef  TYPE_1__ hid_item_t ;

/* Variables and functions */

void
hid_set_data(void *p, const hid_item_t *h, int32_t data)
{
	uint8_t *buf;
	uint32_t hpos;
	uint32_t hsize;
	uint32_t mask;
	int i;
	int end;
	int offs;

	buf = p;

	/* Set report ID byte. */
	if (h->report_ID > 0)
		*buf++ = h->report_ID & 0xff;

	hpos = h->pos;			/* bit position of data */
	hsize = h->report_size;		/* bit length of data */

	if (hsize != 32) {
		mask = (1 << hsize) - 1;
		data &= mask;
	} else
		mask = ~0;

	data <<= (hpos % 8);
	mask <<= (hpos % 8);
	mask = ~mask;

	offs = hpos / 8;
	end = (hpos + hsize) / 8 - offs;

	for (i = 0; i <= end; i++)
		buf[offs + i] = (buf[offs + i] & (mask >> (i*8))) |
		    ((data >> (i*8)) & 0xff);
}