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
typedef  int uint32_t ;
struct hid_item {int kind; int pos; int report_size; int report_count; scalar_t__ report_ID; } ;
struct hid_data {int dummy; } ;
typedef  int /*<<< orphan*/  report_desc_t ;
typedef  enum hid_kind { ____Placeholder_hid_kind } hid_kind ;

/* Variables and functions */
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
 scalar_t__ hid_get_item (struct hid_data*,struct hid_item*) ; 
 struct hid_data* hid_start_parse (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memset (struct hid_item*,int /*<<< orphan*/ ,int) ; 

int
hid_report_size(report_desc_t r, enum hid_kind k, int id)
{
	struct hid_data *d;
	struct hid_item h;
	uint32_t temp;
	uint32_t hpos;
	uint32_t lpos;
	int report_id = 0;

	hpos = 0;
	lpos = 0xFFFFFFFF;

	memset(&h, 0, sizeof h);
	for (d = hid_start_parse(r, 1 << k, id); hid_get_item(d, &h); ) {
		if (h.kind == k) {
			/* compute minimum */
			if (lpos > h.pos)
				lpos = h.pos;
			/* compute end position */
			temp = h.pos + (h.report_size * h.report_count);
			/* compute maximum */
			if (hpos < temp)
				hpos = temp;
			if (h.report_ID != 0)
				report_id = 1;
		}
	}
	hid_end_parse(d);

	/* safety check - can happen in case of currupt descriptors */
	if (lpos > hpos)
		temp = 0;
	else
		temp = hpos - lpos;

	/* return length in bytes rounded up */
	return ((temp + 7) / 8 + report_id);
}