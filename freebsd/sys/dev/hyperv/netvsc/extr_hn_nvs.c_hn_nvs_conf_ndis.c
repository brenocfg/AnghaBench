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
struct hn_softc {scalar_t__ hn_nvs_ver; int hn_caps; int /*<<< orphan*/  hn_ifp; } ;
struct hn_nvs_ndis_conf {int /*<<< orphan*/  nvs_caps; scalar_t__ nvs_mtu; int /*<<< orphan*/  nvs_type; } ;
typedef  int /*<<< orphan*/  conf ;

/* Variables and functions */
 scalar_t__ ETHER_HDR_LEN ; 
 int HN_CAP_MTU ; 
 int HN_CAP_VLAN ; 
 int /*<<< orphan*/  HN_NVS_NDIS_CONF_SRIOV ; 
 int /*<<< orphan*/  HN_NVS_NDIS_CONF_VLAN ; 
 int /*<<< orphan*/  HN_NVS_TYPE_NDIS_CONF ; 
 scalar_t__ HN_NVS_VERSION_5 ; 
 scalar_t__ bootverbose ; 
 int hn_nvs_req_send (struct hn_softc*,struct hn_nvs_ndis_conf*,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct hn_nvs_ndis_conf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hn_nvs_conf_ndis(struct hn_softc *sc, int mtu)
{
	struct hn_nvs_ndis_conf conf;
	int error;

	memset(&conf, 0, sizeof(conf));
	conf.nvs_type = HN_NVS_TYPE_NDIS_CONF;
	conf.nvs_mtu = mtu + ETHER_HDR_LEN;
	conf.nvs_caps = HN_NVS_NDIS_CONF_VLAN;
	if (sc->hn_nvs_ver >= HN_NVS_VERSION_5)
		conf.nvs_caps |= HN_NVS_NDIS_CONF_SRIOV;

	/* NOTE: No response. */
	error = hn_nvs_req_send(sc, &conf, sizeof(conf));
	if (error) {
		if_printf(sc->hn_ifp, "send nvs ndis conf failed: %d\n", error);
		return (error);
	}

	if (bootverbose)
		if_printf(sc->hn_ifp, "nvs ndis conf done\n");
	sc->hn_caps |= HN_CAP_MTU | HN_CAP_VLAN;
	return (0);
}