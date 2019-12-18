#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sfxge_softc {int /*<<< orphan*/  vpd_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  vpd_size; int /*<<< orphan*/  enp; } ;
struct TYPE_3__ {size_t evv_length; scalar_t__* evv_value; int /*<<< orphan*/  evv_tag; } ;
typedef  TYPE_1__ efx_vpd_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int EACCES ; 
 int /*<<< orphan*/  EFX_VPD_ID ; 
 int /*<<< orphan*/  EFX_VPD_RO ; 
 int /*<<< orphan*/  M_SFXGE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ efx_vpd_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int efx_vpd_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int efx_vpd_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_vpd_try_add (struct sfxge_softc*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
sfxge_vpd_init(struct sfxge_softc *sc)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->dev);
	struct sysctl_oid *vpd_node;
	struct sysctl_oid_list *vpd_list;
	char keyword[3];
	efx_vpd_value_t value;
	int rc;

	if ((rc = efx_vpd_size(sc->enp, &sc->vpd_size)) != 0) {
		/*
		 * Unpriviledged functions deny VPD access.
		 * Simply skip VPD in this case.
		 */
		if (rc == EACCES)
			goto done;
		goto fail;
	}
	sc->vpd_data = malloc(sc->vpd_size, M_SFXGE, M_WAITOK);
	if ((rc = efx_vpd_read(sc->enp, sc->vpd_data, sc->vpd_size)) != 0)
		goto fail2;

	/* Copy ID (product name) into device description, and log it. */
	value.evv_tag = EFX_VPD_ID;
	if (efx_vpd_get(sc->enp, sc->vpd_data, sc->vpd_size, &value) == 0) {
		value.evv_value[value.evv_length] = 0;
		device_set_desc_copy(sc->dev, value.evv_value);
		device_printf(sc->dev, "%s\n", value.evv_value);
	}

	vpd_node = SYSCTL_ADD_NODE(
		ctx, SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev)),
		OID_AUTO, "vpd", CTLFLAG_RD, NULL, "Vital Product Data");
	vpd_list = SYSCTL_CHILDREN(vpd_node);

	/* Add sysctls for all expected and any vendor-defined keywords. */
	sfxge_vpd_try_add(sc, vpd_list, EFX_VPD_RO, "PN");
	sfxge_vpd_try_add(sc, vpd_list, EFX_VPD_RO, "EC");
	sfxge_vpd_try_add(sc, vpd_list, EFX_VPD_RO, "SN");
	keyword[0] = 'V';
	keyword[2] = 0;
	for (keyword[1] = '0'; keyword[1] <= '9'; keyword[1]++)
		sfxge_vpd_try_add(sc, vpd_list, EFX_VPD_RO, keyword);
	for (keyword[1] = 'A'; keyword[1] <= 'Z'; keyword[1]++)
		sfxge_vpd_try_add(sc, vpd_list, EFX_VPD_RO, keyword);

done:
	return (0);

fail2:
	free(sc->vpd_data, M_SFXGE);
fail:
	return (rc);
}