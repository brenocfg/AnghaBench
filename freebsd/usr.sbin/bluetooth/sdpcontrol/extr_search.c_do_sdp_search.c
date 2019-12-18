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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  size_t int32_t ;
struct TYPE_3__ {scalar_t__ flags; int attr; int vlen; int value; } ;

/* Variables and functions */
 int BSIZE ; 
 int ERROR ; 
 int OK ; 
#define  SDP_ATTR_BLUETOOTH_PROFILE_DESCRIPTOR_LIST 131 
 scalar_t__ SDP_ATTR_INVALID ; 
 scalar_t__ SDP_ATTR_OK ; 
#define  SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST 130 
#define  SDP_ATTR_SERVICE_CLASS_ID_LIST 129 
#define  SDP_ATTR_SERVICE_RECORD_HANDLE 128 
 size_t SDP_DATA_UINT32 ; 
 int /*<<< orphan*/  SDP_GET32 (size_t,int) ; 
 int /*<<< orphan*/  SDP_GET8 (size_t,int) ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_COMMON_ISDN_ACCESS ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_CORDLESS_TELEPHONY ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_DIALUP_NETWORKING ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_FAX ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_GN ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_HEADSET ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_HUMAN_INTERFACE_DEVICE ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_LAN_ACCESS_USING_PPP ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_NAP ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_OBEX_FILE_TRANSFER ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_OBEX_OBJECT_PUSH ; 
 int /*<<< orphan*/  SDP_SERVICE_CLASS_SERIAL_PORT ; 
 int USAGE ; 
 int /*<<< orphan*/  attrs ; 
 int /*<<< orphan*/  attrs_len ; 
 int* buffer ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_bluetooth_profile_descriptor_list (int,int) ; 
 int /*<<< orphan*/  print_protocol_descriptor_list (int,int) ; 
 int /*<<< orphan*/  print_service_class_id_list (int,int) ; 
 size_t sdp_search (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 size_t strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  tolower (char) ; 
 TYPE_1__* values ; 
 size_t values_len ; 

__attribute__((used)) static int
do_sdp_search(void *xs, int argc, char **argv)
{
	char		*ep = NULL;
	int32_t		 n, type, value;
	uint16_t	 service;

	/* Parse command line arguments */
	switch (argc) {
	case 1:
		n = strtoul(argv[0], &ep, 16);
		if (*ep != 0) {
			switch (tolower(argv[0][0])) {
			case 'c': /* CIP/CTP */
				switch (tolower(argv[0][1])) {
				case 'i':
					service = SDP_SERVICE_CLASS_COMMON_ISDN_ACCESS;
					break;

				case 't':
					service = SDP_SERVICE_CLASS_CORDLESS_TELEPHONY;
					break;

				default:
					return (USAGE);
					/* NOT REACHED */
				}
				break;

			case 'd': /* DialUp Networking */
				service = SDP_SERVICE_CLASS_DIALUP_NETWORKING;
				break;

			case 'f': /* Fax/OBEX File Transfer */
				switch (tolower(argv[0][1])) {
				case 'a':
					service = SDP_SERVICE_CLASS_FAX;
					break;

				case 't':
					service = SDP_SERVICE_CLASS_OBEX_FILE_TRANSFER;
					break;

				default:
					return (USAGE);
					/* NOT REACHED */
				}
				break;

			case 'g': /* GN */
				service = SDP_SERVICE_CLASS_GN;
				break;

			case 'h': /* Headset/HID */
				switch (tolower(argv[0][1])) {
				case 'i':
					service = SDP_SERVICE_CLASS_HUMAN_INTERFACE_DEVICE;
					break;

				case 's':
					service = SDP_SERVICE_CLASS_HEADSET;
					break;

				default:
					return (USAGE);
					/* NOT REACHED */
				}
				break;

			case 'l': /* LAN Access Using PPP */
				service = SDP_SERVICE_CLASS_LAN_ACCESS_USING_PPP;
				break;

			case 'n': /* NAP */
				service = SDP_SERVICE_CLASS_NAP;
				break;

			case 'o': /* OBEX Object Push */
				service = SDP_SERVICE_CLASS_OBEX_OBJECT_PUSH;
				break;

			case 's': /* Serial Port */
				service = SDP_SERVICE_CLASS_SERIAL_PORT;
				break;

			default:
				return (USAGE);
				/* NOT REACHED */
			}
		} else
			service = (uint16_t) n;
		break;

	default:
		return (USAGE);
	}

	/* Initialize attribute values array */
	for (n = 0; n < values_len; n ++) {
		values[n].flags = SDP_ATTR_INVALID;
		values[n].attr = 0;
		values[n].vlen = BSIZE;
		values[n].value = buffer[n];
	}

	/* Do SDP Service Search Attribute Request */
	n = sdp_search(xs, 1, &service, attrs_len, attrs, values_len, values);
	if (n != 0)
		return (ERROR);

	/* Print attributes values */
	for (n = 0; n < values_len; n ++) {
		if (values[n].flags != SDP_ATTR_OK)
			break;

		switch (values[n].attr) {
		case SDP_ATTR_SERVICE_RECORD_HANDLE:
			fprintf(stdout, "\n");
			if (values[n].vlen == 5) {
				SDP_GET8(type, values[n].value);
				if (type == SDP_DATA_UINT32) {
					SDP_GET32(value, values[n].value);
					fprintf(stdout, "Record Handle: " \
							"%#8.8x\n", value);
				} else
					fprintf(stderr, "Invalid type=%#x " \
							"Record Handle " \
							"attribute!\n", type);
			} else
				fprintf(stderr, "Invalid size=%d for Record " \
						"Handle attribute\n",
						values[n].vlen);
			break;

		case SDP_ATTR_SERVICE_CLASS_ID_LIST:
			fprintf(stdout, "Service Class ID List:\n");
			print_service_class_id_list(values[n].value,
					values[n].value + values[n].vlen);
			break;

		case SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST:
			fprintf(stdout, "Protocol Descriptor List:\n");
			print_protocol_descriptor_list(values[n].value,
					values[n].value + values[n].vlen);
			break;

		case SDP_ATTR_BLUETOOTH_PROFILE_DESCRIPTOR_LIST:
			fprintf(stdout, "Bluetooth Profile Descriptor List:\n");
			print_bluetooth_profile_descriptor_list(values[n].value,
					values[n].value + values[n].vlen);
			break;

		default:
			fprintf(stderr, "Unexpected attribute ID=%#4.4x\n",
					values[n].attr);
			break;
		}
	}

	return (OK);
}