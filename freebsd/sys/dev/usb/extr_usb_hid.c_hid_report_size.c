#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_size_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int pos; int size; int count; } ;
struct hid_item {int kind; scalar_t__ report_ID; TYPE_1__ loc; } ;
struct hid_data {int dummy; } ;
typedef  enum hid_kind { ____Placeholder_hid_kind } hid_kind ;

/* Variables and functions */
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
 scalar_t__ hid_get_item (struct hid_data*,struct hid_item*) ; 
 struct hid_data* hid_start_parse (void const*,int /*<<< orphan*/ ,int) ; 

int
hid_report_size(const void *buf, usb_size_t len, enum hid_kind k, uint8_t *id)
{
	struct hid_data *d;
	struct hid_item h;
	uint32_t temp;
	uint32_t hpos;
	uint32_t lpos;
	uint8_t any_id;

	any_id = 0;
	hpos = 0;
	lpos = 0xFFFFFFFF;

	for (d = hid_start_parse(buf, len, 1 << k); hid_get_item(d, &h);) {
		if (h.kind == k) {
			/* check for ID-byte presence */
			if ((h.report_ID != 0) && !any_id) {
				if (id != NULL)
					*id = h.report_ID;
				any_id = 1;
			}
			/* compute minimum */
			if (lpos > h.loc.pos)
				lpos = h.loc.pos;
			/* compute end position */
			temp = h.loc.pos + (h.loc.size * h.loc.count);
			/* compute maximum */
			if (hpos < temp)
				hpos = temp;
		}
	}
	hid_end_parse(d);

	/* safety check - can happen in case of currupt descriptors */
	if (lpos > hpos)
		temp = 0;
	else
		temp = hpos - lpos;

	/* check for ID byte */
	if (any_id)
		temp += 8;
	else if (id != NULL)
		*id = 0;

	/* return length in bytes rounded up */
	return ((temp + 7) / 8);
}