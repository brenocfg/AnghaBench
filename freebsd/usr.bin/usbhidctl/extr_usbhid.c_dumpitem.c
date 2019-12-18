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
struct hid_item {int flags; int report_ID; int pos; int report_size; int report_count; int logical_minimum; int logical_maximum; int physical_minimum; int physical_maximum; int unit; int unit_exponent; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  HID_PAGE (int /*<<< orphan*/ ) ; 
 int HIO_CONST ; 
 int HIO_VARIABLE ; 
 char* hid_usage_in_page (int /*<<< orphan*/ ) ; 
 char* hid_usage_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static void
dumpitem(const char *label, struct hid_item *h)
{
	if ((h->flags & HIO_CONST) && !verbose)
		return;
	printf("%s rid=%d pos=%d size=%d count=%d page=%s usage=%s%s%s", label,
	       h->report_ID, h->pos, h->report_size, h->report_count,
	       hid_usage_page(HID_PAGE(h->usage)),
	       hid_usage_in_page(h->usage),
	       h->flags & HIO_CONST ? " Const" : "",
	       h->flags & HIO_VARIABLE ? "" : " Array");
	printf(", logical range %d..%d",
	       h->logical_minimum, h->logical_maximum);
	if (h->physical_minimum != h->physical_maximum)
		printf(", physical range %d..%d",
		       h->physical_minimum, h->physical_maximum);
	if (h->unit)
		printf(", unit=0x%02x exp=%d", h->unit, h->unit_exponent);
	printf("\n");
}