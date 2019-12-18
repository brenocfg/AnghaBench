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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sfxge_softc {int /*<<< orphan*/  enp; int /*<<< orphan*/  stats_node; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_U64 ; 
 unsigned int EFX_MAC_NSTATS ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char const*,int,struct sfxge_softc*,unsigned int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 char* efx_mac_stat_name (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sfxge_mac_stat_handler ; 

__attribute__((used)) static void
sfxge_mac_stat_init(struct sfxge_softc *sc)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->dev);
	struct sysctl_oid_list *stat_list;
	unsigned int id;
	const char *name;

	stat_list = SYSCTL_CHILDREN(sc->stats_node);

	/* Initialise the named stats */
	for (id = 0; id < EFX_MAC_NSTATS; id++) {
		name = efx_mac_stat_name(sc->enp, id);
		SYSCTL_ADD_PROC(
			ctx, stat_list,
			OID_AUTO, name, CTLTYPE_U64|CTLFLAG_RD,
			sc, id, sfxge_mac_stat_handler, "Q",
			"");
	}
}