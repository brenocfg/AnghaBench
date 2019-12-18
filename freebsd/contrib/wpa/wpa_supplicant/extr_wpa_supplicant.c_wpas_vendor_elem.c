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
struct wpa_supplicant {struct wpa_supplicant* p2pdev; } ;
typedef  enum wpa_vendor_elem_frame { ____Placeholder_wpa_vendor_elem_frame } wpa_vendor_elem_frame ;

/* Variables and functions */
#define  VENDOR_ELEM_BEACON_P2P_GO 140 
#define  VENDOR_ELEM_P2P_ASSOC_REQ 139 
#define  VENDOR_ELEM_P2P_ASSOC_RESP 138 
#define  VENDOR_ELEM_P2P_GO_NEG_CONF 137 
#define  VENDOR_ELEM_P2P_GO_NEG_REQ 136 
#define  VENDOR_ELEM_P2P_GO_NEG_RESP 135 
#define  VENDOR_ELEM_P2P_INV_REQ 134 
#define  VENDOR_ELEM_P2P_INV_RESP 133 
#define  VENDOR_ELEM_P2P_PD_REQ 132 
#define  VENDOR_ELEM_P2P_PD_RESP 131 
#define  VENDOR_ELEM_PROBE_REQ_P2P 130 
#define  VENDOR_ELEM_PROBE_RESP_P2P 129 
#define  VENDOR_ELEM_PROBE_RESP_P2P_GO 128 

struct wpa_supplicant *
wpas_vendor_elem(struct wpa_supplicant *wpa_s, enum wpa_vendor_elem_frame frame)
{
	switch (frame) {
#ifdef CONFIG_P2P
	case VENDOR_ELEM_PROBE_REQ_P2P:
	case VENDOR_ELEM_PROBE_RESP_P2P:
	case VENDOR_ELEM_PROBE_RESP_P2P_GO:
	case VENDOR_ELEM_BEACON_P2P_GO:
	case VENDOR_ELEM_P2P_PD_REQ:
	case VENDOR_ELEM_P2P_PD_RESP:
	case VENDOR_ELEM_P2P_GO_NEG_REQ:
	case VENDOR_ELEM_P2P_GO_NEG_RESP:
	case VENDOR_ELEM_P2P_GO_NEG_CONF:
	case VENDOR_ELEM_P2P_INV_REQ:
	case VENDOR_ELEM_P2P_INV_RESP:
	case VENDOR_ELEM_P2P_ASSOC_REQ:
	case VENDOR_ELEM_P2P_ASSOC_RESP:
		return wpa_s->p2pdev;
#endif /* CONFIG_P2P */
	default:
		return wpa_s;
	}
}