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
typedef  int u8 ;

/* Variables and functions */
#define  EAP_TYPE_FAST 140 
#define  EAP_TYPE_GTC 139 
#define  EAP_TYPE_IDENTITY 138 
#define  EAP_TYPE_MD5 137 
#define  EAP_TYPE_NAK 136 
#define  EAP_TYPE_NOTIFICATION 135 
#define  EAP_TYPE_OTP 134 
#define  EAP_TYPE_PEAP 133 
#define  EAP_TYPE_PSK 132 
#define  EAP_TYPE_SAKE 131 
#define  EAP_TYPE_SIM 130 
#define  EAP_TYPE_TLS 129 
#define  EAP_TYPE_TTLS 128 

__attribute__((used)) static char *eap_type_text(u8 type)
{
	switch (type) {
	case EAP_TYPE_IDENTITY: return "Identity";
	case EAP_TYPE_NOTIFICATION: return "Notification";
	case EAP_TYPE_NAK: return "Nak";
	case EAP_TYPE_TLS: return "TLS";
	case EAP_TYPE_TTLS: return "TTLS";
	case EAP_TYPE_PEAP: return "PEAP";
	case EAP_TYPE_SIM: return "SIM";
	case EAP_TYPE_GTC: return "GTC";
	case EAP_TYPE_MD5: return "MD5";
	case EAP_TYPE_OTP: return "OTP";
	case EAP_TYPE_FAST: return "FAST";
	case EAP_TYPE_SAKE: return "SAKE";
	case EAP_TYPE_PSK: return "PSK";
	default: return "Unknown";
	}
}