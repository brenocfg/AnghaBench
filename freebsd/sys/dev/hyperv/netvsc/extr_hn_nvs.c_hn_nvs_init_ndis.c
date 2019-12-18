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
struct hn_softc {int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_ndis_ver; } ;
struct hn_nvs_ndis_init {int /*<<< orphan*/  nvs_ndis_minor; int /*<<< orphan*/  nvs_ndis_major; int /*<<< orphan*/  nvs_type; } ;
typedef  int /*<<< orphan*/  ndis ;

/* Variables and functions */
 int /*<<< orphan*/  HN_NDIS_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HN_NDIS_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HN_NVS_TYPE_NDIS_INIT ; 
 int hn_nvs_req_send (struct hn_softc*,struct hn_nvs_ndis_init*,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct hn_nvs_ndis_init*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hn_nvs_init_ndis(struct hn_softc *sc)
{
	struct hn_nvs_ndis_init ndis;
	int error;

	memset(&ndis, 0, sizeof(ndis));
	ndis.nvs_type = HN_NVS_TYPE_NDIS_INIT;
	ndis.nvs_ndis_major = HN_NDIS_VERSION_MAJOR(sc->hn_ndis_ver);
	ndis.nvs_ndis_minor = HN_NDIS_VERSION_MINOR(sc->hn_ndis_ver);

	/* NOTE: No response. */
	error = hn_nvs_req_send(sc, &ndis, sizeof(ndis));
	if (error)
		if_printf(sc->hn_ifp, "send nvs ndis init failed: %d\n", error);
	return (error);
}