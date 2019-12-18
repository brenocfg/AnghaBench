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
struct sfxge_softc {int /*<<< orphan*/  stats_node; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sfxge_softc*,unsigned int,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 unsigned int nitems (TYPE_1__*) ; 
 int /*<<< orphan*/  sfxge_rx_stat_handler ; 
 TYPE_1__* sfxge_rx_stats ; 

__attribute__((used)) static void
sfxge_rx_stat_init(struct sfxge_softc *sc)
{
	struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(sc->dev);
	struct sysctl_oid_list *stat_list;
	unsigned int id;

	stat_list = SYSCTL_CHILDREN(sc->stats_node);

	for (id = 0; id < nitems(sfxge_rx_stats); id++) {
		SYSCTL_ADD_PROC(
			ctx, stat_list,
			OID_AUTO, sfxge_rx_stats[id].name,
			CTLTYPE_UINT|CTLFLAG_RD,
			sc, id, sfxge_rx_stat_handler, "IU",
			"");
	}
}