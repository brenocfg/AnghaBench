#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int /*<<< orphan*/  b_hnp_enable; int /*<<< orphan*/  otg_port; } ;
struct usb_hcd {TYPE_3__ self; } ;
struct admhcd {int num_ports; TYPE_2__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {TYPE_1__ roothub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMHC_PS_CPP ; 
 int /*<<< orphan*/  ADMHC_PS_CPS ; 
 int /*<<< orphan*/  ADMHC_PS_CSC ; 
 int /*<<< orphan*/  ADMHC_PS_OCIC ; 
 int /*<<< orphan*/  ADMHC_PS_PESC ; 
 int /*<<< orphan*/  ADMHC_PS_PRSC ; 
 int /*<<< orphan*/  ADMHC_PS_PSSC ; 
 int /*<<< orphan*/  ADMHC_PS_SPP ; 
 int /*<<< orphan*/  ADMHC_PS_SPS ; 
 int /*<<< orphan*/  ADMHC_RH_OCIC ; 
#define  C_HUB_LOCAL_POWER 145 
#define  C_HUB_OVER_CURRENT 144 
#define  ClearHubFeature 143 
#define  ClearPortFeature 142 
 int EPIPE ; 
 int ESHUTDOWN ; 
#define  GetHubDescriptor 141 
#define  GetHubStatus 140 
#define  GetPortStatus 139 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
#define  SetHubFeature 138 
#define  SetPortFeature 137 
#define  USB_PORT_FEAT_C_CONNECTION 136 
#define  USB_PORT_FEAT_C_ENABLE 135 
#define  USB_PORT_FEAT_C_OVER_CURRENT 134 
#define  USB_PORT_FEAT_C_RESET 133 
#define  USB_PORT_FEAT_C_SUSPEND 132 
#define  USB_PORT_FEAT_ENABLE 131 
#define  USB_PORT_FEAT_POWER 130 
#define  USB_PORT_FEAT_RESET 129 
#define  USB_PORT_FEAT_SUSPEND 128 
 int admhc_get_hub_descriptor (struct admhcd*,char*) ; 
 int admhc_get_hub_status (struct admhcd*,char*) ; 
 int admhc_get_port_status (struct admhcd*,int,char*) ; 
 int admhc_port_disable (struct admhcd*,int) ; 
 int admhc_port_enable (struct admhcd*,int) ; 
 int admhc_port_reset (struct admhcd*,int) ; 
 int admhc_port_write (struct admhcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  admhc_writel (struct admhcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct admhcd* hcd_to_admhcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  start_hnp (struct admhcd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int admhc_hub_control(struct usb_hcd *hcd, u16 typeReq, u16 wValue,
		u16 wIndex, char *buf, u16 wLength)
{
	struct admhcd	*ahcd = hcd_to_admhcd(hcd);
	int		ports = ahcd->num_ports;
	int		ret = 0;

	if (unlikely(!HCD_HW_ACCESSIBLE(hcd)))
		return -ESHUTDOWN;

	switch (typeReq) {
	case ClearHubFeature:
		switch (wValue) {
		case C_HUB_OVER_CURRENT:
#if 0			/* FIXME */
			admhc_writel(ahcd, ADMHC_RH_OCIC,
					&ahcd->regs->roothub.status);
#endif
		case C_HUB_LOCAL_POWER:
			break;
		default:
			goto error;
		}
		break;
	case ClearPortFeature:
		if (!wIndex || wIndex > ports)
			goto error;
		wIndex--;

		switch (wValue) {
		case USB_PORT_FEAT_ENABLE:
			ret = admhc_port_disable(ahcd, wIndex);
			break;
		case USB_PORT_FEAT_SUSPEND:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_CPS);
			break;
		case USB_PORT_FEAT_POWER:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_CPP);
			break;
		case USB_PORT_FEAT_C_CONNECTION:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_CSC);
			break;
		case USB_PORT_FEAT_C_ENABLE:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_PESC);
			break;
		case USB_PORT_FEAT_C_SUSPEND:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_PSSC);
			break;
		case USB_PORT_FEAT_C_OVER_CURRENT:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_OCIC);
			break;
		case USB_PORT_FEAT_C_RESET:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_PRSC);
			break;
		default:
			goto error;
		}
		break;
	case GetHubDescriptor:
		ret = admhc_get_hub_descriptor(ahcd, buf);
		break;
	case GetHubStatus:
		ret = admhc_get_hub_status(ahcd, buf);
		break;
	case GetPortStatus:
		if (!wIndex || wIndex > ports)
			goto error;
		wIndex--;

		ret = admhc_get_port_status(ahcd, wIndex, buf);
		break;
	case SetHubFeature:
		switch (wValue) {
		case C_HUB_OVER_CURRENT:
			/* FIXME:  this can be cleared, yes? */
		case C_HUB_LOCAL_POWER:
			break;
		default:
			goto error;
		}
		break;
	case SetPortFeature:
		if (!wIndex || wIndex > ports)
			goto error;
		wIndex--;

		switch (wValue) {
		case USB_PORT_FEAT_ENABLE:
			ret = admhc_port_enable(ahcd, wIndex);
			break;
		case USB_PORT_FEAT_RESET:
			ret = admhc_port_reset(ahcd, wIndex);
			break;
		case USB_PORT_FEAT_SUSPEND:
#ifdef	CONFIG_USB_OTG
			if (hcd->self.otg_port == (wIndex + 1)
					&& hcd->self.b_hnp_enable)
				start_hnp(ahcd);
			else
#endif
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_SPS);
			break;
		case USB_PORT_FEAT_POWER:
			ret = admhc_port_write(ahcd, wIndex, ADMHC_PS_SPP);
			break;
		default:
			goto error;
		}
		break;

	default:
error:
		/* "protocol stall" on error */
		ret = -EPIPE;
	}

	return ret;
}