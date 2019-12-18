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
#define  SKU_APAC 144 
#define  SKU_APAC2 143 
#define  SKU_APAC3 142 
#define  SKU_CA 141 
#define  SKU_DEBUG 140 
#define  SKU_ETSI 139 
#define  SKU_ETSI2 138 
#define  SKU_ETSI3 137 
#define  SKU_FCC 136 
#define  SKU_FCC3 135 
#define  SKU_GZ901 134 
#define  SKU_JAPAN 133 
#define  SKU_KOREA 132 
#define  SKU_NONE 131 
#define  SKU_ROW 130 
#define  SKU_SR9 129 
#define  SKU_XR9 128 
 int WlanRegDomainCode_apac ; 
 int WlanRegDomainCode_apac2 ; 
 int WlanRegDomainCode_apac3 ; 
 int WlanRegDomainCode_ca ; 
 int WlanRegDomainCode_debug ; 
 int WlanRegDomainCode_etsi ; 
 int WlanRegDomainCode_etsi2 ; 
 int WlanRegDomainCode_etsi3 ; 
 int WlanRegDomainCode_fcc ; 
 int WlanRegDomainCode_fcc3 ; 
 int WlanRegDomainCode_gz901 ; 
 int WlanRegDomainCode_japan ; 
 int WlanRegDomainCode_korea ; 
 int WlanRegDomainCode_none ; 
 int WlanRegDomainCode_row ; 
 int WlanRegDomainCode_sr9 ; 
 int WlanRegDomainCode_xr9 ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static enum WlanRegDomainCode
wlan_regdomain_to_snmp(int which)
{
	enum WlanRegDomainCode reg_domain;

	switch (which) {
	case SKU_FCC:
		reg_domain = WlanRegDomainCode_fcc;
		break;
	case SKU_CA:
		reg_domain = WlanRegDomainCode_ca;
		break;
	case SKU_ETSI:
		reg_domain = WlanRegDomainCode_etsi;
		break;
	case SKU_ETSI2:
		reg_domain = WlanRegDomainCode_etsi2;
		break;
	case SKU_ETSI3:
		reg_domain = WlanRegDomainCode_etsi3;
		break;
	case SKU_FCC3:
		reg_domain = WlanRegDomainCode_fcc3;
		break;
	case SKU_JAPAN:
		reg_domain = WlanRegDomainCode_japan;
		break;
	case SKU_KOREA:
		reg_domain = WlanRegDomainCode_korea;
		break;
	case SKU_APAC:
		reg_domain = WlanRegDomainCode_apac;
		break;
	case SKU_APAC2:
		reg_domain = WlanRegDomainCode_apac2;
		break;
	case SKU_APAC3:
		reg_domain = WlanRegDomainCode_apac3;
		break;
	case SKU_ROW:
		reg_domain = WlanRegDomainCode_row;
		break;
	case SKU_NONE:
		reg_domain = WlanRegDomainCode_none;
		break;
	case SKU_DEBUG:
		reg_domain = WlanRegDomainCode_debug;
		break;
	case SKU_SR9:
		reg_domain = WlanRegDomainCode_sr9;
		break;
	case SKU_XR9:
		reg_domain = WlanRegDomainCode_xr9;
		break;
	case SKU_GZ901:
		reg_domain = WlanRegDomainCode_gz901;
		break;
	case 0:
		reg_domain = WlanRegDomainCode_none;
		break;
	default:
		syslog(LOG_ERR, "unknown regdomain (0x%x) ", which);
		reg_domain = WlanRegDomainCode_none;
		break;
	}

	return (reg_domain);
}