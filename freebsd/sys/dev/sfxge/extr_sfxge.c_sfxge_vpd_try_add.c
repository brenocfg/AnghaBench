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
struct sysctl_ctx_list {int dummy; } ;
struct sfxge_softc {int /*<<< orphan*/  vpd_size; int /*<<< orphan*/  vpd_data; int /*<<< orphan*/  enp; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int evv_tag; int evv_keyword; } ;
typedef  TYPE_1__ efx_vpd_value_t ;
typedef  int efx_vpd_tag_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_STRING ; 
 int EFX_VPD_KEYWORD (char const,char const) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char const*,int,struct sfxge_softc*,int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 scalar_t__ efx_vpd_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sfxge_vpd_handler ; 

__attribute__((used)) static void
sfxge_vpd_try_add(struct sfxge_softc *sc, struct sysctl_oid_list *list,
		  efx_vpd_tag_t tag, const char *keyword)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->dev);
	efx_vpd_value_t value;

	/* Check whether VPD tag/keyword is present */
	value.evv_tag = tag;
	value.evv_keyword = EFX_VPD_KEYWORD(keyword[0], keyword[1]);
	if (efx_vpd_get(sc->enp, sc->vpd_data, sc->vpd_size, &value) != 0)
		return;

	SYSCTL_ADD_PROC(
		ctx, list, OID_AUTO, keyword, CTLTYPE_STRING|CTLFLAG_RD,
		sc, tag << 16 | EFX_VPD_KEYWORD(keyword[0], keyword[1]),
		sfxge_vpd_handler, "A", "");
}