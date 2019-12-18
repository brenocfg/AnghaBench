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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  force_fs ;

/* Variables and functions */
 int errno ; 
 int get_integer () ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  show_host_device_selection (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  show_host_modem_test (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  show_host_msc_test (int /*<<< orphan*/ ,int,int,int) ; 
 int sysctlbyname (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  usb_control_ep_error_test (int,int) ; 
 int /*<<< orphan*/  usb_get_descriptor_test (int,int,int) ; 
 int /*<<< orphan*/  usb_get_string_desc_test (int,int) ; 
 int /*<<< orphan*/  usb_port_reset_test (int,int,int) ; 
 int /*<<< orphan*/  usb_set_alt_interface_test (int,int) ; 
 int /*<<< orphan*/  usb_set_and_clear_stall_test (int,int) ; 
 int /*<<< orphan*/  usb_set_config_test (int,int,int) ; 
 int /*<<< orphan*/  usb_suspend_resume_test (int,int,int) ; 
 int usb_ts_show_menu (int,char*,char*,int,int,char*,int) ; 

__attribute__((used)) static void
show_host_select(uint8_t level)
{
	int force_fs = 0;
	int error;
	uint32_t duration = 60;

	uint16_t dev_vid = 0;
	uint16_t dev_pid = 0;
	uint8_t retval;

	while (1) {

		error = sysctlbyname("hw.usb.ehci.no_hs", NULL, NULL,
		    &force_fs, sizeof(force_fs));

		if (error != 0) {
			printf("WARNING: Could not set non-FS mode "
			    "to %d (error=%d)\n", force_fs, errno);
		}
		retval = usb_ts_show_menu(level, "Select Host Mode Test (via LibUSB)",
		    " 1) Select USB device (VID=0x%04x, PID=0x%04x)\n"
		    " 2) Manually enter USB vendor and product ID\n"
		    " 3) Force FULL speed operation: <%s>\n"
		    " 4) Mass Storage (UMASS)\n"
		    " 5) Modem (UMODEM)\n"
		    "10) Start String Descriptor Test\n"
		    "11) Start Port Reset Test\n"
		    "12) Start Set Config Test\n"
		    "13) Start Get Descriptor Test\n"
		    "14) Start Suspend and Resume Test\n"
		    "15) Start Set and Clear Endpoint Stall Test\n"
		    "16) Start Set Alternate Interface Setting Test\n"
		    "17) Start Invalid Control Request Test\n"
		    "30) Duration: <%d> seconds\n"
		    "x) Return to previous menu\n",
		    dev_vid, dev_pid,
		    force_fs ? "YES" : "NO",
		    (int)duration);

		switch (retval) {
		case 0:
			break;
		case 1:
			show_host_device_selection(level + 1, &dev_vid, &dev_pid);
			break;
		case 2:
			dev_vid = get_integer() & 0xFFFF;
			dev_pid = get_integer() & 0xFFFF;
			break;
		case 3:
			force_fs ^= 1;
			break;
		case 4:
			show_host_msc_test(level + 1, dev_vid, dev_pid, duration);
			break;
		case 5:
			show_host_modem_test(level + 1, dev_vid, dev_pid, duration);
			break;
		case 10:
			usb_get_string_desc_test(dev_vid, dev_pid);
			break;
		case 11:
			usb_port_reset_test(dev_vid, dev_pid, duration);
			break;
		case 12:
			usb_set_config_test(dev_vid, dev_pid, duration);
			break;
		case 13:
			usb_get_descriptor_test(dev_vid, dev_pid, duration);
			break;
		case 14:
			usb_suspend_resume_test(dev_vid, dev_pid, duration);
			break;
		case 15:
			usb_set_and_clear_stall_test(dev_vid, dev_pid);
			break;
		case 16:
			usb_set_alt_interface_test(dev_vid, dev_pid);
			break;
		case 17:
			usb_control_ep_error_test(dev_vid, dev_pid);
			break;
		case 30:
			duration = get_integer();
			break;
		default:
			return;
		}
	}
}