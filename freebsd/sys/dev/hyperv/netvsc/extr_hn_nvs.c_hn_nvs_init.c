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
struct hn_softc {int /*<<< orphan*/  hn_caps; int /*<<< orphan*/  hn_nvs_ver; int /*<<< orphan*/  hn_ifp; int /*<<< orphan*/  hn_ndis_ver; int /*<<< orphan*/  hn_dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  HN_CAP_HASHVAL ; 
 int /*<<< orphan*/  HN_NDIS_VERSION_6_1 ; 
 int /*<<< orphan*/  HN_NDIS_VERSION_6_30 ; 
 int /*<<< orphan*/  HN_NDIS_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HN_NDIS_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HN_NVS_VERSION_4 ; 
 int /*<<< orphan*/  HN_NVS_VERSION_5 ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int hn_nvs_doinit (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hn_nvs_version ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hn_nvs_init(struct hn_softc *sc)
{
	int i, error;

	if (device_is_attached(sc->hn_dev)) {
		/*
		 * NVS version and NDIS version MUST NOT be changed.
		 */
		if (bootverbose) {
			if_printf(sc->hn_ifp, "reinit NVS version 0x%x, "
			    "NDIS version %u.%u\n", sc->hn_nvs_ver,
			    HN_NDIS_VERSION_MAJOR(sc->hn_ndis_ver),
			    HN_NDIS_VERSION_MINOR(sc->hn_ndis_ver));
		}

		error = hn_nvs_doinit(sc, sc->hn_nvs_ver);
		if (error) {
			if_printf(sc->hn_ifp, "reinit NVS version 0x%x "
			    "failed: %d\n", sc->hn_nvs_ver, error);
			return (error);
		}
		goto done;
	}

	/*
	 * Find the supported NVS version and set NDIS version accordingly.
	 */
	for (i = 0; i < nitems(hn_nvs_version); ++i) {
		error = hn_nvs_doinit(sc, hn_nvs_version[i]);
		if (!error) {
			sc->hn_nvs_ver = hn_nvs_version[i];

			/* Set NDIS version according to NVS version. */
			sc->hn_ndis_ver = HN_NDIS_VERSION_6_30;
			if (sc->hn_nvs_ver <= HN_NVS_VERSION_4)
				sc->hn_ndis_ver = HN_NDIS_VERSION_6_1;

			if (bootverbose) {
				if_printf(sc->hn_ifp, "NVS version 0x%x, "
				    "NDIS version %u.%u\n", sc->hn_nvs_ver,
				    HN_NDIS_VERSION_MAJOR(sc->hn_ndis_ver),
				    HN_NDIS_VERSION_MINOR(sc->hn_ndis_ver));
			}
			goto done;
		}
	}
	if_printf(sc->hn_ifp, "no NVS available\n");
	return (ENXIO);

done:
	if (sc->hn_nvs_ver >= HN_NVS_VERSION_5)
		sc->hn_caps |= HN_CAP_HASHVAL;
	return (0);
}