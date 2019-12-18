#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct hid_device {size_t control_psm; size_t interrupt_psm; int reconnect_initiate; int battery_power; int normally_connectable; int /*<<< orphan*/ * desc; void* version; void* product_id; void* vendor_id; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  name; } ;
typedef  size_t int32_t ;
typedef  void* int16_t ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_6__ {scalar_t__ flags; int attr; size_t vlen; int /*<<< orphan*/ * value; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOATTR ; 
 scalar_t__ ENOMEM ; 
 int HCI_DEVNAME_SIZE ; 
 int /*<<< orphan*/ * NG_HCI_BDADDR_ANY ; 
#define  SDP_ATTR_ADDITIONAL_PROTOCOL_DESCRIPTOR_LISTS 132 
#define  SDP_ATTR_DEVICE_ID_SERVICE_PRODUCTID 131 
#define  SDP_ATTR_DEVICE_ID_SERVICE_VENDORID 130 
#define  SDP_ATTR_DEVICE_ID_SERVICE_VERSION 129 
 scalar_t__ SDP_ATTR_INVALID ; 
 scalar_t__ SDP_ATTR_OK ; 
#define  SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST 128 
 size_t SDP_DATA_UINT16 ; 
 int /*<<< orphan*/  SDP_GET16 (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDP_GET8 (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * attrs ; 
 int /*<<< orphan*/  attrs_devid ; 
 scalar_t__ bt_devname (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_devremote_name_gen (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_init_return_values () ; 
 size_t hid_sdp_parse_boolean (TYPE_1__*) ; 
 int /*<<< orphan*/  hid_sdp_parse_hid_descriptor (TYPE_1__*) ; 
 size_t hid_sdp_parse_protocol_descriptor_list (TYPE_1__*) ; 
 int /*<<< orphan*/  hid_sdp_query_exit (scalar_t__) ; 
 int /*<<< orphan*/ * hid_use_report_desc (int /*<<< orphan*/ *,size_t) ; 
 int nattrs ; 
 size_t nvalues ; 
 int /*<<< orphan*/  sdp_close (void*) ; 
 scalar_t__ sdp_error (void*) ; 
 scalar_t__ sdp_get_lcaddr (void*,int /*<<< orphan*/ *) ; 
 void* sdp_open (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ sdp_search (void*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  service ; 
 int /*<<< orphan*/  service_devid ; 
 TYPE_1__* values ; 

__attribute__((used)) static int32_t
hid_sdp_query(bdaddr_t const *local, struct hid_device *hd, int32_t *error)
{
	void			*ss = NULL;
	uint8_t			*hid_descriptor = NULL, *v;
	int32_t			 i, control_psm = -1, interrupt_psm = -1,
				 reconnect_initiate = -1,
				 normally_connectable = 0, battery_power = 0,
				 hid_descriptor_length = -1, type;
	int16_t 		 vendor_id = 0, product_id = 0, version = 0;
	bdaddr_t		 sdp_local;
	char			 devname[HCI_DEVNAME_SIZE];

	if (local == NULL)
		local = NG_HCI_BDADDR_ANY;
	if (hd == NULL)
		hid_sdp_query_exit(EINVAL);

	hid_init_return_values();

	if ((ss = sdp_open(local, &hd->bdaddr)) == NULL)
		hid_sdp_query_exit(ENOMEM);
	if (sdp_error(ss) != 0)
		hid_sdp_query_exit(sdp_error(ss));
	if (sdp_search(ss, 1, &service, nattrs, attrs, nvalues, values) != 0)
                hid_sdp_query_exit(sdp_error(ss));

	for (i = 0; i < nvalues; i ++) {
		if (values[i].flags != SDP_ATTR_OK)
			continue;

		switch (values[i].attr) {
		case SDP_ATTR_PROTOCOL_DESCRIPTOR_LIST:
			control_psm = hid_sdp_parse_protocol_descriptor_list(&values[i]);
			break;

		case SDP_ATTR_ADDITIONAL_PROTOCOL_DESCRIPTOR_LISTS:
			interrupt_psm = hid_sdp_parse_protocol_descriptor_list(&values[i]);
			break;

		case 0x0205: /* HIDReconnectInitiate */
			reconnect_initiate = hid_sdp_parse_boolean(&values[i]);
			break;

		case 0x0206: /* HIDDescriptorList */
			if (hid_sdp_parse_hid_descriptor(&values[i]) == 0) {
				hid_descriptor = values[i].value;
				hid_descriptor_length = values[i].vlen;
			}
			break;

		case 0x0209: /* HIDBatteryPower */
			battery_power = hid_sdp_parse_boolean(&values[i]);
			break;

		case 0x020d: /* HIDNormallyConnectable */
			normally_connectable = hid_sdp_parse_boolean(&values[i]);
			break;
		}
	}

	hid_init_return_values();

	if (sdp_search(ss, 1, &service_devid, 1, &attrs_devid, nvalues, values) != 0)
                hid_sdp_query_exit(sdp_error(ss));

	/* Try extract HCI bdaddr from opened SDP session */
	if (sdp_get_lcaddr(ss, &sdp_local) != 0 ||
	    bt_devname(devname, &sdp_local) == 0)
		hid_sdp_query_exit(ENOATTR);

        sdp_close(ss);
        ss = NULL;

	/* If search is successful, scan through return vals */
	for (i = 0; i < 3; i ++ ) {
		if (values[i].flags == SDP_ATTR_INVALID )
			continue;

		/* Expecting tag + uint16_t on all 3 attributes */
		if (values[i].vlen != 3)
			continue;

		/* Make sure, we're reading a uint16_t */
		v = values[i].value;
		SDP_GET8(type, v);
		if (type != SDP_DATA_UINT16 )
			continue;

		switch (values[i].attr) {
			case SDP_ATTR_DEVICE_ID_SERVICE_VENDORID:
				SDP_GET16(vendor_id, v);
				break;
			case SDP_ATTR_DEVICE_ID_SERVICE_PRODUCTID:
				SDP_GET16(product_id, v);
				break;
			case SDP_ATTR_DEVICE_ID_SERVICE_VERSION:
				SDP_GET16(version, v);
				break;
			default:
				break;
		}
	}

	if (control_psm == -1 || interrupt_psm == -1 ||
	    reconnect_initiate == -1 ||
	    hid_descriptor == NULL || hid_descriptor_length == -1)
		hid_sdp_query_exit(ENOATTR);
	hd->name = bt_devremote_name_gen(devname, &hd->bdaddr);
	hd->vendor_id = vendor_id;
	hd->product_id = product_id;
	hd->version = version;
	hd->control_psm = control_psm;
	hd->interrupt_psm = interrupt_psm;
	hd->reconnect_initiate = reconnect_initiate? 1 : 0;
	hd->battery_power = battery_power? 1 : 0;
	hd->normally_connectable = normally_connectable? 1 : 0;
	hd->desc = hid_use_report_desc(hid_descriptor, hid_descriptor_length);
	if (hd->desc == NULL)
		hid_sdp_query_exit(ENOMEM);

	return (0);
}