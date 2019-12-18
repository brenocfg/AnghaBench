#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hid_data {int dummy; } ;
typedef  int /*<<< orphan*/  report_desc_t ;
struct TYPE_4__ {int kind; int flags; unsigned int usage; scalar_t__ report_size; } ;
typedef  TYPE_1__ hid_item_t ;
typedef  enum hid_kind { ____Placeholder_hid_kind } hid_kind ;

/* Variables and functions */
 int HIO_CONST ; 
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
 scalar_t__ hid_get_item (struct hid_data*,TYPE_1__*) ; 
 struct hid_data* hid_start_parse (int /*<<< orphan*/ ,int,int) ; 

int
hid_locate(report_desc_t desc, unsigned int u, enum hid_kind k,
	   hid_item_t *h, int id)
{
	struct hid_data *d;

	for (d = hid_start_parse(desc, 1 << k, id); hid_get_item(d, h); ) {
		if (h->kind == k && !(h->flags & HIO_CONST) && h->usage == u) {
			hid_end_parse(d);
			return (1);
		}
	}
	hid_end_parse(d);
	h->report_size = 0;
	return (0);
}