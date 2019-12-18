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
typedef  scalar_t__ uint16_t ;
struct usb_interface_descriptor {scalar_t__ bInterfaceClass; int bInterfaceSubClass; int bInterfaceProtocol; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 scalar_t__ UICLASS_MASS ; 
#define  UIPROTO_MASS_BBB 136 
#define  UIPROTO_MASS_BBB_OLD 135 
#define  UIPROTO_MASS_CBI 134 
#define  UIPROTO_MASS_CBI_I 133 
#define  UISUBCLASS_RBC 132 
#define  UISUBCLASS_SCSI 131 
#define  UISUBCLASS_SFF8020I 130 
#define  UISUBCLASS_SFF8070I 129 
#define  UISUBCLASS_UFI 128 
 scalar_t__ UMASS_PROTO_ATAPI ; 
 scalar_t__ UMASS_PROTO_BBB ; 
 scalar_t__ UMASS_PROTO_CBI ; 
 scalar_t__ UMASS_PROTO_CBI_I ; 
 scalar_t__ UMASS_PROTO_RBC ; 
 scalar_t__ UMASS_PROTO_SCSI ; 
 scalar_t__ UMASS_PROTO_UFI ; 
 struct usb_interface_descriptor* usbd_get_interface_descriptor (struct usb_interface*) ; 

__attribute__((used)) static uint16_t
umass_get_proto(struct usb_interface *iface)
{
	struct usb_interface_descriptor *id;
	uint16_t retval;

	retval = 0;

	/* Check for a standards compliant device */
	id = usbd_get_interface_descriptor(iface);
	if ((id == NULL) ||
	    (id->bInterfaceClass != UICLASS_MASS)) {
		goto done;
	}
	switch (id->bInterfaceSubClass) {
	case UISUBCLASS_SCSI:
		retval |= UMASS_PROTO_SCSI;
		break;
	case UISUBCLASS_UFI:
		retval |= UMASS_PROTO_UFI;
		break;
	case UISUBCLASS_RBC:
		retval |= UMASS_PROTO_RBC;
		break;
	case UISUBCLASS_SFF8020I:
	case UISUBCLASS_SFF8070I:
		retval |= UMASS_PROTO_ATAPI;
		break;
	default:
		goto done;
	}

	switch (id->bInterfaceProtocol) {
	case UIPROTO_MASS_CBI:
		retval |= UMASS_PROTO_CBI;
		break;
	case UIPROTO_MASS_CBI_I:
		retval |= UMASS_PROTO_CBI_I;
		break;
	case UIPROTO_MASS_BBB_OLD:
	case UIPROTO_MASS_BBB:
		retval |= UMASS_PROTO_BBB;
		break;
	default:
		goto done;
	}
done:
	return (retval);
}