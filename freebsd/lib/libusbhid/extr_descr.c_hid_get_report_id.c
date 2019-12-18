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
typedef  int /*<<< orphan*/ * report_desc_t ;
struct TYPE_3__ {int report_ID; } ;
typedef  TYPE_1__ hid_item_t ;
typedef  int /*<<< orphan*/  hid_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_GET_REPORT_ID ; 
 int /*<<< orphan*/  hid_dispose_report_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_end_parse (int /*<<< orphan*/ ) ; 
 int hid_feature ; 
 scalar_t__ hid_get_item (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * hid_get_report_desc (int) ; 
 int hid_get_report_id_compat7 (int) ; 
 int hid_input ; 
 int hid_output ; 
 int /*<<< orphan*/  hid_start_parse (int /*<<< orphan*/ *,int,int) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 

int
hid_get_report_id(int fd)
{
	report_desc_t rep;
	hid_data_t d;
	hid_item_t h;
	int kindset;
	int temp = -1;
	int ret;

	if ((rep = hid_get_report_desc(fd)) == NULL)
		goto use_ioctl;
	kindset = 1 << hid_input | 1 << hid_output | 1 << hid_feature;
	for (d = hid_start_parse(rep, kindset, -1); hid_get_item(d, &h); ) {
		/* Return the first report ID we met. */
		if (h.report_ID != 0) {
			temp = h.report_ID;
			break;
		}
	}
	hid_end_parse(d);
	hid_dispose_report_desc(rep);

	if (temp > 0)
		return (temp);

use_ioctl:
	ret = ioctl(fd, USB_GET_REPORT_ID, &temp);
#ifdef HID_COMPAT7
	if (ret < 0)
		ret = hid_get_report_id_compat7(fd);
	else
#endif
		ret = temp;

	return (ret);
}