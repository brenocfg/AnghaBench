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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct sfxge_intr {int n_alloc; scalar_t__ state; } ;
struct sfxge_softc {int evq_count; int /*<<< orphan*/ * evqs_stats_node; struct sysctl_oid* stats_node; int /*<<< orphan*/  dev; int /*<<< orphan*/  ev_moderation; struct sfxge_intr intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 scalar_t__ SFXGE_INTR_INITIALIZED ; 
 int /*<<< orphan*/  SFXGE_MODERATION ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct sfxge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_ev_qfini (struct sfxge_softc*,int) ; 
 int sfxge_ev_qinit (struct sfxge_softc*,int) ; 
 int /*<<< orphan*/  sfxge_ev_stat_init (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_int_mod_handler ; 

int
sfxge_ev_init(struct sfxge_softc *sc)
{
	struct sysctl_ctx_list *sysctl_ctx = device_get_sysctl_ctx(sc->dev);
	struct sysctl_oid *sysctl_tree = device_get_sysctl_tree(sc->dev);
	struct sfxge_intr *intr;
	int index;
	int rc;

	intr = &sc->intr;

	sc->evq_count = intr->n_alloc;

	KASSERT(intr->state == SFXGE_INTR_INITIALIZED,
	    ("intr->state != SFXGE_INTR_INITIALIZED"));

	/* Set default interrupt moderation; add a sysctl to
	 * read and change it.
	 */
	sc->ev_moderation = SFXGE_MODERATION;
	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
			OID_AUTO, "int_mod", CTLTYPE_UINT|CTLFLAG_RW,
			sc, 0, sfxge_int_mod_handler, "IU",
			"sfxge interrupt moderation (us)");

#if EFSYS_OPT_QSTATS
	sc->evqs_stats_node = SYSCTL_ADD_NODE(
		device_get_sysctl_ctx(sc->dev), SYSCTL_CHILDREN(sc->stats_node),
		OID_AUTO, "evq", CTLFLAG_RD, NULL, "Event queues stats");
	if (sc->evqs_stats_node == NULL) {
		rc = ENOMEM;
		goto fail_evqs_stats_node;
	}
#endif

	/*
	 * Initialize the event queue(s) - one per interrupt.
	 */
	for (index = 0; index < sc->evq_count; index++) {
		if ((rc = sfxge_ev_qinit(sc, index)) != 0)
			goto fail;
	}

#if EFSYS_OPT_QSTATS
	sfxge_ev_stat_init(sc);
#endif

	return (0);

fail:
	while (--index >= 0)
		sfxge_ev_qfini(sc, index);

#if EFSYS_OPT_QSTATS
fail_evqs_stats_node:
#endif
	sc->evq_count = 0;
	return (rc);
}