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
typedef  int /*<<< orphan*/  usb_size_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct hid_location {scalar_t__ size; } ;
struct hid_item {int kind; int flags; scalar_t__ usage; int /*<<< orphan*/  report_ID; struct hid_location loc; } ;
struct hid_data {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  enum hid_kind { ____Placeholder_hid_kind } hid_kind ;

/* Variables and functions */
 int HIO_CONST ; 
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
 scalar_t__ hid_get_item (struct hid_data*,struct hid_item*) ; 
 struct hid_data* hid_start_parse (void const*,int /*<<< orphan*/ ,int) ; 

int
hid_locate(const void *desc, usb_size_t size, int32_t u, enum hid_kind k,
    uint8_t index, struct hid_location *loc, uint32_t *flags, uint8_t *id)
{
	struct hid_data *d;
	struct hid_item h;

	for (d = hid_start_parse(desc, size, 1 << k); hid_get_item(d, &h);) {
		if (h.kind == k && !(h.flags & HIO_CONST) && h.usage == u) {
			if (index--)
				continue;
			if (loc != NULL)
				*loc = h.loc;
			if (flags != NULL)
				*flags = h.flags;
			if (id != NULL)
				*id = h.report_ID;
			hid_end_parse(d);
			return (1);
		}
	}
	if (loc != NULL)
		loc->size = 0;
	if (flags != NULL)
		*flags = 0;
	if (id != NULL)
		*id = 0;
	hid_end_parse(d);
	return (0);
}