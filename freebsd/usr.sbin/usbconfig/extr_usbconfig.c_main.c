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
typedef  void* uint8_t ;
struct TYPE_2__ {int bmRequestType; int wLength; void* wIndex; void* wValue; void* bRequest; } ;
struct options {int got_add_quirk; char* quirkname; int got_remove_quirk; int got_add_device_quirk; int got_remove_device_quirk; int got_detach_kernel_driver; int got_dump_quirk_names; int got_dump_device_quirks; int got_show_iface_driver; int bus; int addr; int got_bus; int got_addr; int got_iface; int got_set_config; int got_set_alt; int got_set_template; int got_get_template; int got_dump_all_desc; int got_dump_device_desc; int got_dump_curr_config; int got_dump_all_config; int got_dump_info; int got_dump_string; int got_suspend; int got_resume; int got_power_off; int got_power_save; int got_power_on; int got_reset; int got_list; int got_do_request; scalar_t__ got_any; TYPE_1__ setup; int /*<<< orphan*/ * buffer; void* string_index; int /*<<< orphan*/  template; void* alt_index; void* config_index; void* iface; void* hi_rev; void* lo_rev; void* pid; void* vid; } ;
struct libusb20_backend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBUSB20_CONTROL_SETUP ; 
 int LIBUSB20_ENDPOINT_IN ; 
 int /*<<< orphan*/  LIBUSB20_INIT (int /*<<< orphan*/ ,TYPE_1__*) ; 
#define  T_ADDR 157 
#define  T_ADD_DEVICE_QUIRK 156 
#define  T_ADD_QUIRK 155 
#define  T_DETACH_KERNEL_DRIVER 154 
#define  T_DO_REQUEST 153 
#define  T_DUMP_ALL_CONFIG_DESC 152 
#define  T_DUMP_ALL_DESC 151 
#define  T_DUMP_CURR_CONFIG_DESC 150 
#define  T_DUMP_DEVICE_DESC 149 
#define  T_DUMP_DEVICE_QUIRKS 148 
#define  T_DUMP_INFO 147 
#define  T_DUMP_QUIRK_NAMES 146 
#define  T_DUMP_STRING 145 
#define  T_GET_TEMPLATE 144 
#define  T_IFACE 143 
#define  T_LIST 142 
#define  T_POWER_OFF 141 
#define  T_POWER_ON 140 
#define  T_POWER_SAVE 139 
#define  T_REMOVE_DEVICE_QUIRK 138 
#define  T_REMOVE_QUIRK 137 
#define  T_RESET 136 
#define  T_RESUME 135 
#define  T_SET_ALT 134 
#define  T_SET_CONFIG 133 
#define  T_SET_TEMPLATE 132 
#define  T_SHOW_IFACE_DRIVER 131 
#define  T_SUSPEND 130 
#define  T_UGEN 129 
#define  T_UNIT 128 
 int /*<<< orphan*/  duplicate_option (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  flush_command (struct libusb20_backend*,struct options*) ; 
 int /*<<< orphan*/  get_int (char*) ; 
 int get_token (char*,int) ; 
 struct libusb20_backend* libusb20_be_alloc_default () ; 
 int /*<<< orphan*/  libusb20_be_free (struct libusb20_backend*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 void* num_id (char*,char*) ; 
 struct options options ; 
 int sscanf (char const*,char*,int*,int*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	struct libusb20_backend *pbe;
	struct options *opt = &options;
	const char *ptr;
	int unit;
	int addr;
	int n;
	int t;

	if (argc < 1) {
		usage();
	}
	pbe = libusb20_be_alloc_default();
	if (pbe == NULL)
		err(1, "could not access USB backend\n");

	for (n = 1; n != argc; n++) {

		/* get number of additional options */
		t = (argc - n - 1);
		if (t > 255)
			t = 255;
		switch (get_token(argv[n], t)) {
		case T_ADD_QUIRK:
			if (opt->got_add_quirk) {
				flush_command(pbe, opt);
			}
			opt->quirkname = argv[n + 1];
			n++;

			opt->got_add_quirk = 1;
			opt->got_any++;
			break;

		case T_REMOVE_QUIRK:
			if (opt->got_remove_quirk) {
				flush_command(pbe, opt);
			}
			opt->quirkname = argv[n + 1];
			n++;

			opt->got_remove_quirk = 1;
			opt->got_any++;
			break;

		case T_ADD_DEVICE_QUIRK:
			if (opt->got_add_device_quirk) {
				flush_command(pbe, opt);
			}
			opt->vid = num_id(argv[n + 1], "Vendor ID");
			opt->pid = num_id(argv[n + 2], "Product ID");
			opt->lo_rev = num_id(argv[n + 3], "Low Revision");
			opt->hi_rev = num_id(argv[n + 4], "High Revision");
			opt->quirkname = argv[n + 5];
			n += 5;

			opt->got_add_device_quirk = 1;
			opt->got_any++;
			break;

		case T_REMOVE_DEVICE_QUIRK:
			if (opt->got_remove_device_quirk) {
				flush_command(pbe, opt);
			}
			opt->vid = num_id(argv[n + 1], "Vendor ID");
			opt->pid = num_id(argv[n + 2], "Product ID");
			opt->lo_rev = num_id(argv[n + 3], "Low Revision");
			opt->hi_rev = num_id(argv[n + 4], "High Revision");
			opt->quirkname = argv[n + 5];
			n += 5;
			opt->got_remove_device_quirk = 1;
			opt->got_any++;
			break;

		case T_DETACH_KERNEL_DRIVER:
			if (opt->got_detach_kernel_driver)
				duplicate_option(argv[n]);
			opt->got_detach_kernel_driver = 1;
			opt->got_any++;
			break;

		case T_DUMP_QUIRK_NAMES:
			if (opt->got_dump_quirk_names)
				duplicate_option(argv[n]);
			opt->got_dump_quirk_names = 1;
			opt->got_any++;
			break;

		case T_DUMP_DEVICE_QUIRKS:
			if (opt->got_dump_device_quirks)
				duplicate_option(argv[n]);
			opt->got_dump_device_quirks = 1;
			opt->got_any++;
			break;

		case T_SHOW_IFACE_DRIVER:
			opt->got_show_iface_driver = 1;
			break;

		case T_UGEN:
			if (opt->got_any) {
				/* allow multiple commands on the same line */
				flush_command(pbe, opt);
			}
			ptr = argv[n + 1];

			if ((ptr[0] == 'u') &&
			    (ptr[1] == 'g') &&
			    (ptr[2] == 'e') &&
			    (ptr[3] == 'n'))
				ptr += 4;

			if ((sscanf(ptr, "%d.%d",
			    &unit, &addr) != 2) ||
			    (unit < 0) || (unit > 65535) ||
			    (addr < 0) || (addr > 65535)) {
				errx(1, "cannot "
				    "parse '%s'", argv[n + 1]);
			}
			opt->bus = unit;
			opt->addr = addr;
			opt->got_bus = 1;
			opt->got_addr = 1;
			n++;
			break;

		case T_UNIT:
			if (opt->got_any) {
				/* allow multiple commands on the same line */
				flush_command(pbe, opt);
			}
			opt->bus = num_id(argv[n + 1], "busnum");
			opt->got_bus = 1;
			n++;
			break;
		case T_ADDR:
			opt->addr = num_id(argv[n + 1], "addr");
			opt->got_addr = 1;
			n++;
			break;
		case T_IFACE:
			opt->iface = num_id(argv[n + 1], "iface");
			opt->got_iface = 1;
			n++;
			break;
		case T_SET_CONFIG:
			if (opt->got_set_config)
				duplicate_option(argv[n]);
			opt->config_index = num_id(argv[n + 1], "cfg_index");
			opt->got_set_config = 1;
			opt->got_any++;
			n++;
			break;
		case T_SET_ALT:
			if (opt->got_set_alt)
				duplicate_option(argv[n]);
			opt->alt_index = num_id(argv[n + 1], "cfg_index");
			opt->got_set_alt = 1;
			opt->got_any++;
			n++;
			break;
		case T_SET_TEMPLATE:
			if (opt->got_set_template)
				duplicate_option(argv[n]);
			opt->template = get_int(argv[n + 1]);
			opt->got_set_template = 1;
			opt->got_any++;
			n++;
			break;
		case T_GET_TEMPLATE:
			if (opt->got_get_template)
				duplicate_option(argv[n]);
			opt->got_get_template = 1;
			opt->got_any++;
			break;
		case T_DUMP_ALL_DESC:
			if (opt->got_dump_all_desc)
				duplicate_option(argv[n]);
			opt->got_dump_all_desc = 1;
			opt->got_any++;
			break;
		case T_DUMP_DEVICE_DESC:
			if (opt->got_dump_device_desc)
				duplicate_option(argv[n]);
			opt->got_dump_device_desc = 1;
			opt->got_any++;
			break;
		case T_DUMP_CURR_CONFIG_DESC:
			if (opt->got_dump_curr_config)
				duplicate_option(argv[n]);
			opt->got_dump_curr_config = 1;
			opt->got_any++;
			break;
		case T_DUMP_ALL_CONFIG_DESC:
			if (opt->got_dump_all_config)
				duplicate_option(argv[n]);
			opt->got_dump_all_config = 1;
			opt->got_any++;
			break;
		case T_DUMP_INFO:
			if (opt->got_dump_info)
				duplicate_option(argv[n]);
			opt->got_dump_info = 1;
			opt->got_any++;
			break;
		case T_DUMP_STRING:
			if (opt->got_dump_string)
				duplicate_option(argv[n]);
			opt->string_index = num_id(argv[n + 1], "str_index");
			opt->got_dump_string = 1;
			opt->got_any++;
			n++;
			break;
		case T_SUSPEND:
			if (opt->got_suspend)
				duplicate_option(argv[n]);
			opt->got_suspend = 1;
			opt->got_any++;
			break;
		case T_RESUME:
			if (opt->got_resume)
				duplicate_option(argv[n]);
			opt->got_resume = 1;
			opt->got_any++;
			break;
		case T_POWER_OFF:
			if (opt->got_power_off)
				duplicate_option(argv[n]);
			opt->got_power_off = 1;
			opt->got_any++;
			break;
		case T_POWER_SAVE:
			if (opt->got_power_save)
				duplicate_option(argv[n]);
			opt->got_power_save = 1;
			opt->got_any++;
			break;
		case T_POWER_ON:
			if (opt->got_power_on)
				duplicate_option(argv[n]);
			opt->got_power_on = 1;
			opt->got_any++;
			break;
		case T_RESET:
			if (opt->got_reset)
				duplicate_option(argv[n]);
			opt->got_reset = 1;
			opt->got_any++;
			break;
		case T_LIST:
			if (opt->got_list)
				duplicate_option(argv[n]);
			opt->got_list = 1;
			opt->got_any++;
			break;
		case T_DO_REQUEST:
			if (opt->got_do_request)
				duplicate_option(argv[n]);
			LIBUSB20_INIT(LIBUSB20_CONTROL_SETUP, &opt->setup);
			opt->setup.bmRequestType = num_id(argv[n + 1], "bmReqTyp");
			opt->setup.bRequest = num_id(argv[n + 2], "bReq");
			opt->setup.wValue = num_id(argv[n + 3], "wVal");
			opt->setup.wIndex = num_id(argv[n + 4], "wIndex");
			opt->setup.wLength = num_id(argv[n + 5], "wLen");
			if (opt->setup.wLength != 0) {
				opt->buffer = malloc(opt->setup.wLength);
			} else {
				opt->buffer = NULL;
			}

			n += 5;

			if (!(opt->setup.bmRequestType &
			    LIBUSB20_ENDPOINT_IN)) {
				/* copy in data */
				t = (argc - n - 1);
				if (t < opt->setup.wLength) {
					err(1, "request data missing");
				}
				t = opt->setup.wLength;
				while (t--) {
					((uint8_t *)opt->buffer)[t] =
					    num_id(argv[n + t + 1], "req_data");
				}
				n += opt->setup.wLength;
			}
			opt->got_do_request = 1;
			opt->got_any++;
			break;
		default:
			if (n == 1) {
				ptr = argv[n];

				if ((ptr[0] == 'u') &&
				    (ptr[1] == 'g') &&
				    (ptr[2] == 'e') &&
				    (ptr[3] == 'n'))
					ptr += 4;

				if ((sscanf(ptr, "%d.%d",
				    &unit, &addr) != 2) ||
				    (unit < 0) || (unit > 65535) ||
				    (addr < 0) || (addr > 65535)) {
					usage();
					break;
				}

				opt->bus = unit;
				opt->addr = addr;
				opt->got_bus = 1;
				opt->got_addr = 1;
				break;
			}
			usage();
			break;
		}
	}
	if (opt->got_any) {
		/* flush out last command */
		flush_command(pbe, opt);
	} else {
		/* list all the devices */
		opt->got_list = 1;
		opt->got_any++;
		flush_command(pbe, opt);
	}
	/* release data */
	libusb20_be_free(pbe);

	return (0);
}