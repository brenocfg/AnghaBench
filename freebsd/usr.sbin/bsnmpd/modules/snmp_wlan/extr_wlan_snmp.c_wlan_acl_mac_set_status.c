#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint ;
struct wlan_mac_mac {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  macsupported; } ;
struct TYPE_3__ {int integer; } ;
struct snmp_value {TYPE_1__ v; int /*<<< orphan*/  var; } ;
struct snmp_context {TYPE_2__* scratch; } ;
struct TYPE_4__ {int int1; } ;

/* Variables and functions */
 int IEEE80211_ADDR_LEN ; 
 int IFNAMSIZ ; 
 int RowStatus_active ; 
#define  RowStatus_createAndGo 129 
#define  RowStatus_destroy 128 
 int SNMP_ERR_GENERR ; 
 int SNMP_ERR_INCONS_NAME ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int SNMP_ERR_NOSUCHNAME ; 
 scalar_t__ wlan_add_mac_acl_mac (struct wlan_iface*,struct wlan_mac_mac*) ; 
 struct wlan_mac_mac* wlan_get_acl_mac (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct wlan_iface**) ; 
 scalar_t__ wlan_mac_add_mac (struct wlan_iface*,struct wlan_mac_mac*) ; 
 int /*<<< orphan*/  wlan_mac_delete_mac (struct wlan_iface*,struct wlan_mac_mac*) ; 
 int /*<<< orphan*/  wlan_mac_free_mac (struct wlan_mac_mac*) ; 
 scalar_t__ wlan_mac_index_decode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct wlan_mac_mac* wlan_mac_new_mac (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
wlan_acl_mac_set_status(struct snmp_context *ctx, struct snmp_value *val,
    uint sub)
{
	char wname[IFNAMSIZ];
	uint8_t mac[IEEE80211_ADDR_LEN];
	struct wlan_iface *wif;
	struct wlan_mac_mac *macl;

	if (wlan_mac_index_decode(&val->var, sub, wname, mac) < 0)
		return (SNMP_ERR_GENERR);
	macl = wlan_get_acl_mac(&val->var, sub, &wif);

	switch (val->v.integer) {
	case RowStatus_createAndGo:
		if (macl != NULL)
			return (SNMP_ERR_INCONS_NAME);
		break;
	case RowStatus_destroy:
		if (macl == NULL)
			return (SNMP_ERR_NOSUCHNAME);
		ctx->scratch->int1 = RowStatus_active;
		return (SNMP_ERR_NOERROR);
	default:
		return (SNMP_ERR_INCONS_VALUE);
	}


	if (wif == NULL || !wif->macsupported)
		return (SNMP_ERR_INCONS_VALUE);

	if ((macl = wlan_mac_new_mac((const uint8_t *)mac)) == NULL)
		return (SNMP_ERR_GENERR);

	ctx->scratch->int1 = RowStatus_destroy;

	if (wlan_mac_add_mac(wif, macl) < 0) {
		wlan_mac_free_mac(macl);
		return (SNMP_ERR_GENERR);
	}

	ctx->scratch->int1 = RowStatus_destroy;
	if (wlan_add_mac_acl_mac(wif, macl) < 0) {
		(void)wlan_mac_delete_mac(wif, macl);
		return (SNMP_ERR_GENERR);
	}

	return (SNMP_ERR_NOERROR);
}