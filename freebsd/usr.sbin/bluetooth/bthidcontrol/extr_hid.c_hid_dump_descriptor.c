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
struct hid_item {int kind; int /*<<< orphan*/  usage; } ;
struct hid_data {int dummy; } ;
typedef  int /*<<< orphan*/  report_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  HID_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
#define  hid_collection 132 
 int /*<<< orphan*/  hid_dump_item (char*,struct hid_item*) ; 
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
#define  hid_endcollection 131 
#define  hid_feature 130 
 scalar_t__ hid_get_item (struct hid_data*,struct hid_item*) ; 
#define  hid_input 129 
#define  hid_output 128 
 struct hid_data* hid_start_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* hid_usage_in_page (int /*<<< orphan*/ ) ; 
 char* hid_usage_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
hid_dump_descriptor(report_desc_t r)
{
	struct hid_data	*d = NULL;
	struct hid_item	 h;

	for (d = hid_start_parse(r, ~0, -1); hid_get_item(d, &h); ) {
		switch (h.kind) {
		case hid_collection:
			fprintf(stdout,
"Collection page=%s usage=%s\n", hid_usage_page(HID_PAGE(h.usage)),
				 hid_usage_in_page(h.usage));
			break;

		case hid_endcollection:
			fprintf(stdout, "End collection\n");
			break;

		case hid_input:
			hid_dump_item("Input  ", &h);
			break;

		case hid_output:
			hid_dump_item("Output ", &h);
			break;

		case hid_feature:
			hid_dump_item("Feature", &h);
			break;
		}
	}

	hid_end_parse(d);
}