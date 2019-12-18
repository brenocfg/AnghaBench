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
struct TYPE_3__ {scalar_t__ report_ID; int pos; int report_size; scalar_t__ logical_minimum; scalar_t__ logical_maximum; } ;
typedef  TYPE_1__ hid_item_t ;

/* Variables and functions */

int32_t
hid_get_data(const void *p, const hid_item_t *h)
{
	const uint8_t *buf;
	uint32_t hpos;
	uint32_t hsize;
	uint32_t data;
	int i, end, offs;

	buf = p;

	/* Skip report ID byte. */
	if (h->report_ID > 0)
		buf++;

	hpos = h->pos;			/* bit position of data */
	hsize = h->report_size;		/* bit length of data */

	/* Range check and limit */
	if (hsize == 0)
		return (0);
	if (hsize > 32)
		hsize = 32;

	offs = hpos / 8;
	end = (hpos + hsize) / 8 - offs;
	data = 0;
	for (i = 0; i <= end; i++)
		data |= buf[offs + i] << (i*8);

	/* Correctly shift down data */
	data >>= hpos % 8;
	hsize = 32 - hsize;

	/* Mask and sign extend in one */
	if ((h->logical_minimum < 0) || (h->logical_maximum < 0))
		data = (int32_t)((int32_t)data << hsize) >> hsize;
	else
		data = (uint32_t)((uint32_t)data << hsize) >> hsize;

	return (data);
}