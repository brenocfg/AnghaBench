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
struct hid_item {int kind; int /*<<< orphan*/  usage; int /*<<< orphan*/  collection; } ;
struct hid_data {int dummy; } ;
typedef  int /*<<< orphan*/  report_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  HID_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumpitem (char*,struct hid_item*) ; 
#define  hid_collection 132 
 char* hid_collection_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hid_end_parse (struct hid_data*) ; 
#define  hid_endcollection 131 
#define  hid_feature 130 
 scalar_t__ hid_get_item (struct hid_data*,struct hid_item*) ; 
#define  hid_input 129 
#define  hid_output 128 
 int hid_report_size (int /*<<< orphan*/ ,int const,int) ; 
 struct hid_data* hid_start_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* hid_usage_in_page (int /*<<< orphan*/ ) ; 
 char* hid_usage_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dumpitems(report_desc_t r)
{
	struct hid_data *d;
	struct hid_item h;
	int size;

	for (d = hid_start_parse(r, ~0, -1); hid_get_item(d, &h); ) {
		switch (h.kind) {
		case hid_collection:
			printf("Collection type=%s page=%s usage=%s\n",
			       hid_collection_type(h.collection),
			       hid_usage_page(HID_PAGE(h.usage)),
			       hid_usage_in_page(h.usage));
			break;
		case hid_endcollection:
			printf("End collection\n");
			break;
		case hid_input:
			dumpitem("Input  ", &h);
			break;
		case hid_output:
			dumpitem("Output ", &h);
			break;
		case hid_feature:
			dumpitem("Feature", &h);
			break;
		}
	}
	hid_end_parse(d);
	size = hid_report_size(r, hid_input, -1);
	printf("Total   input size %d bytes\n", size);

	size = hid_report_size(r, hid_output, -1);
	printf("Total  output size %d bytes\n", size);

	size = hid_report_size(r, hid_feature, -1);
	printf("Total feature size %d bytes\n", size);
}