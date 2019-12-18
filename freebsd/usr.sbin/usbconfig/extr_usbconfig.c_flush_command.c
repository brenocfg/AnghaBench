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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_2__ {int bmRequestType; } ;
struct options {int got_suspend; int got_resume; int got_reset; int got_set_config; int got_set_alt; int got_power_save; int got_power_on; int got_power_off; scalar_t__ got_any; int template; scalar_t__ bus; scalar_t__ addr; scalar_t__ got_dump_all_desc; scalar_t__ got_dump_curr_config; scalar_t__ got_dump_all_config; scalar_t__ got_dump_device_desc; int /*<<< orphan*/  got_show_iface_driver; scalar_t__ got_list; scalar_t__ got_dump_info; int /*<<< orphan*/  iface; scalar_t__ got_detach_kernel_driver; int /*<<< orphan*/  alt_index; int /*<<< orphan*/  config_index; scalar_t__ buffer; TYPE_1__ setup; scalar_t__ got_do_request; int /*<<< orphan*/  string_index; scalar_t__ got_dump_string; int /*<<< orphan*/  quirkname; scalar_t__ got_add_quirk; scalar_t__ got_remove_quirk; scalar_t__ got_addr; scalar_t__ got_bus; scalar_t__ got_get_template; scalar_t__ got_set_template; int /*<<< orphan*/  hi_rev; int /*<<< orphan*/  lo_rev; int /*<<< orphan*/  pid; int /*<<< orphan*/  vid; scalar_t__ got_add_device_quirk; scalar_t__ got_remove_device_quirk; scalar_t__ got_dump_device_quirks; scalar_t__ got_dump_quirk_names; } ;
struct libusb20_device {int dummy; } ;
struct libusb20_backend {int dummy; } ;
struct LIBUSB20_DEVICE_DESC_DECODED {int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;

/* Variables and functions */
 int LIBUSB20_ENDPOINT_IN ; 
 int /*<<< orphan*/  LIBUSB20_POWER_OFF ; 
 int /*<<< orphan*/  LIBUSB20_POWER_ON ; 
 int /*<<< orphan*/  LIBUSB20_POWER_RESUME ; 
 int /*<<< orphan*/  LIBUSB20_POWER_SAVE ; 
 int /*<<< orphan*/  LIBUSB20_POWER_SUSPEND ; 
 int /*<<< orphan*/  be_dev_add_quirk (struct libusb20_backend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_dev_remove_quirk (struct libusb20_backend*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_be_dev_quirks (struct libusb20_backend*) ; 
 int /*<<< orphan*/  dump_be_quirk_names (struct libusb20_backend*) ; 
 int /*<<< orphan*/  dump_config (struct libusb20_device*,int) ; 
 int /*<<< orphan*/  dump_device_desc (struct libusb20_device*) ; 
 int /*<<< orphan*/  dump_device_info (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_string_by_index (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ isprint (char) ; 
 struct libusb20_device* libusb20_be_device_foreach (struct libusb20_backend*,struct libusb20_device*) ; 
 scalar_t__ libusb20_be_get_template (struct libusb20_backend*,int*) ; 
 scalar_t__ libusb20_be_set_template (struct libusb20_backend*,int) ; 
 scalar_t__ libusb20_dev_close (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_detach_kernel_driver (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_get_address (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_get_bus_number (struct libusb20_device*) ; 
 struct LIBUSB20_DEVICE_DESC_DECODED* libusb20_dev_get_device_desc (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_open (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_request_sync (struct libusb20_device*,TYPE_1__*,scalar_t__,size_t*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_reset (struct libusb20_device*) ; 
 scalar_t__ libusb20_dev_set_alt_index (struct libusb20_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_set_config_index (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ libusb20_dev_set_power_mode (struct libusb20_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  reset_options (struct options*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
flush_command(struct libusb20_backend *pbe, struct options *opt)
{
	struct libusb20_device *pdev = NULL;
	uint32_t matches = 0;
	uint8_t dump_any;

	/* check for invalid option combinations */
	if ((opt->got_suspend +
	    opt->got_resume +
	    opt->got_reset +
	    opt->got_set_config +
	    opt->got_set_alt +
	    opt->got_power_save +
	    opt->got_power_on +
	    opt->got_power_off) > 1) {
		err(1, "can only specify one of 'set_config', "
		    "'set_alt', 'reset', 'suspend', 'resume', "
		    "'power_save', 'power_on' and 'power_off' "
		    "at the same time!");
	}
	if (opt->got_dump_quirk_names) {
		opt->got_any--;
		dump_be_quirk_names(pbe);
	}
	if (opt->got_dump_device_quirks) {
		opt->got_any--;
		dump_be_dev_quirks(pbe);
	}
	if (opt->got_remove_device_quirk) {
		opt->got_any--;
		be_dev_remove_quirk(pbe,
		    opt->vid, opt->pid, opt->lo_rev, opt->hi_rev, opt->quirkname);
	}
	if (opt->got_add_device_quirk) {
		opt->got_any--;
		be_dev_add_quirk(pbe,
		    opt->vid, opt->pid, opt->lo_rev, opt->hi_rev, opt->quirkname);
	}
	if (opt->got_set_template) {
		opt->got_any--;
		if (libusb20_be_set_template(pbe, opt->template)) {
			fprintf(stderr, "Setting USB template %u failed, "
			    "continuing.\n", opt->template);
		}
	}
	if (opt->got_get_template) {
		opt->got_any--;
		if (libusb20_be_get_template(pbe, &opt->template))
			printf("USB template: <unknown>\n");
		else
			printf("USB template: %u\n", opt->template);
	}
	if (opt->got_any == 0) {
		/*
		 * do not scan through all the devices if there are no valid
		 * options
		 */
		goto done;
	}
	while ((pdev = libusb20_be_device_foreach(pbe, pdev))) {

		if (opt->got_bus &&
		    (libusb20_dev_get_bus_number(pdev) != opt->bus)) {
			continue;
		}
		if (opt->got_addr &&
		    (libusb20_dev_get_address(pdev) != opt->addr)) {
			continue;
		}
		matches++;

		if (opt->got_remove_quirk) {
			struct LIBUSB20_DEVICE_DESC_DECODED *ddesc;
	
			ddesc = libusb20_dev_get_device_desc(pdev);

			be_dev_remove_quirk(pbe,
			    ddesc->idVendor, ddesc->idProduct, 
			    ddesc->bcdDevice, ddesc->bcdDevice,
			    opt->quirkname);
		}

		if (opt->got_add_quirk) {
			struct LIBUSB20_DEVICE_DESC_DECODED *ddesc;
	
			ddesc = libusb20_dev_get_device_desc(pdev);

			be_dev_add_quirk(pbe,
			    ddesc->idVendor, ddesc->idProduct, 
			    ddesc->bcdDevice, ddesc->bcdDevice,
			    opt->quirkname);
		}

		if (libusb20_dev_open(pdev, 0)) {
			err(1, "could not open device");
		}
		if (opt->got_dump_string) {
			dump_string_by_index(pdev, opt->string_index);
		}
		if (opt->got_do_request) {
			uint16_t actlen;
			uint16_t t;

			if (libusb20_dev_request_sync(pdev, &opt->setup,
			    opt->buffer, &actlen, 5000 /* 5 seconds */ , 0)) {
				printf("REQUEST = <ERROR>\n");
			} else if (!(opt->setup.bmRequestType &
			    LIBUSB20_ENDPOINT_IN)) {
				printf("REQUEST = <OK>\n");
			} else {
				t = actlen;
				printf("REQUEST = <");
				for (t = 0; t != actlen; t++) {
					printf("0x%02x%s",
					    ((uint8_t *)opt->buffer)[t],
					    (t == (actlen - 1)) ? "" : " ");
				}
				printf("><");
				for (t = 0; t != actlen; t++) {
					char c;

					c = ((uint8_t *)opt->buffer)[t];
					if ((c != '<') &&
					    (c != '>') && isprint(c)) {
						putchar(c);
					}
				}
				printf(">\n");
			}
		}
		if (opt->got_set_config) {
			if (libusb20_dev_set_config_index(pdev,
			    opt->config_index)) {
				err(1, "could not set config index");
			}
		}
		if (opt->got_set_alt) {
			if (libusb20_dev_set_alt_index(pdev, opt->iface,
			    opt->alt_index)) {
				err(1, "could not set alternate setting");
			}
		}
		if (opt->got_reset) {
			if (libusb20_dev_reset(pdev)) {
				err(1, "could not reset device");
			}
		}
		if (opt->got_suspend) {
			if (libusb20_dev_set_power_mode(pdev,
			    LIBUSB20_POWER_SUSPEND)) {
				err(1, "could not set suspend");
			}
		}
		if (opt->got_resume) {
			if (libusb20_dev_set_power_mode(pdev,
			    LIBUSB20_POWER_RESUME)) {
				err(1, "could not set resume");
			}
		}
		if (opt->got_power_off) {
			if (libusb20_dev_set_power_mode(pdev,
			    LIBUSB20_POWER_OFF)) {
				err(1, "could not set power OFF");
			}
		}
		if (opt->got_power_save) {
			if (libusb20_dev_set_power_mode(pdev,
			    LIBUSB20_POWER_SAVE)) {
				err(1, "could not set power SAVE");
			}
		}
		if (opt->got_power_on) {
			if (libusb20_dev_set_power_mode(pdev,
			    LIBUSB20_POWER_ON)) {
				err(1, "could not set power ON");
			}
		}
		if (opt->got_detach_kernel_driver) {
			if (libusb20_dev_detach_kernel_driver(pdev, opt->iface)) {
				err(1, "could not detach kernel driver");
			}
		}
		dump_any =
		    (opt->got_dump_all_desc ||
		    opt->got_dump_device_desc ||
		    opt->got_dump_curr_config ||
		    opt->got_dump_all_config ||
		    opt->got_dump_info);

		if (opt->got_list || dump_any) {
			dump_device_info(pdev,
			    opt->got_show_iface_driver);
		}
		if (opt->got_dump_device_desc) {
			printf("\n");
			dump_device_desc(pdev);
		}
		if (opt->got_dump_all_config) {
			printf("\n");
			dump_config(pdev, 1);
		} else if (opt->got_dump_curr_config) {
			printf("\n");
			dump_config(pdev, 0);
		} else if (opt->got_dump_all_desc) {
			printf("\n");
			dump_device_desc(pdev);
			dump_config(pdev, 1);
		}
		if (dump_any) {
			printf("\n");
		}
		if (libusb20_dev_close(pdev)) {
			err(1, "could not close device");
		}
	}

	if (matches == 0) {
		printf("No device match or lack of permissions.\n");
	}
done:
	reset_options(opt);

	return;
}