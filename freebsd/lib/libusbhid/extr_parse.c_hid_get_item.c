#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int report_ID; } ;
typedef  TYPE_1__ hid_item_t ;
typedef  TYPE_2__* hid_data_t ;
struct TYPE_8__ {int reportid; } ;

/* Variables and functions */
 int hid_get_item_raw (TYPE_2__*,TYPE_1__*) ; 

int
hid_get_item(hid_data_t s, hid_item_t *h)
{
	int r;

	for (;;) {
		r = hid_get_item_raw(s, h);
		if (r <= 0 || s->reportid == -1 || h->report_ID == s->reportid)
			break;
	}
	return (r);
}