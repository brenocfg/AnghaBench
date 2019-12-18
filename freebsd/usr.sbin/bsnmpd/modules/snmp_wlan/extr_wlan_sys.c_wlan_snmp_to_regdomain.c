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
typedef  enum WlanRegDomainCode { ____Placeholder_WlanRegDomainCode } WlanRegDomainCode ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int SKU_APAC ; 
 int SKU_APAC2 ; 
 int SKU_APAC3 ; 
 int SKU_CA ; 
 int SKU_DEBUG ; 
 int SKU_ETSI ; 
 int SKU_ETSI2 ; 
 int SKU_ETSI3 ; 
 int SKU_FCC ; 
 int SKU_FCC3 ; 
 int SKU_GZ901 ; 
 int SKU_JAPAN ; 
 int SKU_KOREA ; 
 int SKU_NONE ; 
 int SKU_ROW ; 
 int SKU_SR9 ; 
 int SKU_XR9 ; 
#define  WlanRegDomainCode_apac 144 
#define  WlanRegDomainCode_apac2 143 
#define  WlanRegDomainCode_apac3 142 
#define  WlanRegDomainCode_ca 141 
#define  WlanRegDomainCode_debug 140 
#define  WlanRegDomainCode_etsi 139 
#define  WlanRegDomainCode_etsi2 138 
#define  WlanRegDomainCode_etsi3 137 
#define  WlanRegDomainCode_fcc 136 
#define  WlanRegDomainCode_fcc3 135 
#define  WlanRegDomainCode_gz901 134 
#define  WlanRegDomainCode_japan 133 
#define  WlanRegDomainCode_korea 132 
#define  WlanRegDomainCode_none 131 
#define  WlanRegDomainCode_row 130 
#define  WlanRegDomainCode_sr9 129 
#define  WlanRegDomainCode_xr9 128 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
wlan_snmp_to_regdomain(enum WlanRegDomainCode regdomain)
{
	int which;

	switch (regdomain) {
	case WlanRegDomainCode_fcc:
		which = SKU_FCC;
		break;
	case WlanRegDomainCode_ca:
		which = SKU_CA;
		break;
	case WlanRegDomainCode_etsi:
		which = SKU_ETSI;
		break;
	case WlanRegDomainCode_etsi2:
		which = SKU_ETSI2;
		break;
	case WlanRegDomainCode_etsi3:
		which = SKU_ETSI3;
		break;
	case WlanRegDomainCode_fcc3:
		which = SKU_FCC3;
		break;
	case WlanRegDomainCode_japan:
		which = SKU_JAPAN;
		break;
	case WlanRegDomainCode_korea:
		which = SKU_KOREA;
		break;
	case WlanRegDomainCode_apac:
		which = SKU_APAC;
		break;
	case WlanRegDomainCode_apac2:
		which = SKU_APAC2;
		break;
	case WlanRegDomainCode_apac3:
		which = SKU_APAC3;
		break;
	case WlanRegDomainCode_row:
		which = SKU_ROW;
		break;
	case WlanRegDomainCode_none:
		which = SKU_NONE;
		break;
	case WlanRegDomainCode_debug:
		which = SKU_DEBUG;
		break;
	case WlanRegDomainCode_sr9:
		which = SKU_SR9;
		break;
	case WlanRegDomainCode_xr9:
		which = SKU_XR9;
		break;
	case WlanRegDomainCode_gz901:
		which = SKU_GZ901;
		break;
	default:
		syslog(LOG_ERR, "unknown snmp regdomain (0x%x) ", regdomain);
		which = SKU_NONE;
		break;
	}

	return (which);
}