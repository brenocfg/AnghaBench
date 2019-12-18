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
struct tls_dn_field_order_cnt {int cn; int c; int l; int st; int o; int ou; int email; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
#define  NID_commonName 134 
#define  NID_countryName 133 
#define  NID_localityName 132 
#define  NID_organizationName 131 
#define  NID_organizationalUnitName 130 
#define  NID_pkcs9_emailAddress 129 
#define  NID_stateOrProvinceName 128 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int get_dn_field_index(const struct tls_dn_field_order_cnt *dn_cnt,
			      int nid)
{
	switch (nid) {
	case NID_commonName:
		return dn_cnt->cn;
	case NID_countryName:
		return dn_cnt->c;
	case NID_localityName:
		return dn_cnt->l;
	case NID_stateOrProvinceName:
		return dn_cnt->st;
	case NID_organizationName:
		return dn_cnt->o;
	case NID_organizationalUnitName:
		return dn_cnt->ou;
	case NID_pkcs9_emailAddress:
		return dn_cnt->email;
	default:
		wpa_printf(MSG_ERROR,
			   "TLS: Unknown NID '%d' in check_cert_subject",
			   nid);
		return -1;
	}
}