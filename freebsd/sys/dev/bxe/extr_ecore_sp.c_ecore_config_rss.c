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
struct ecore_raw_obj {int (* wait_comp ) (struct bxe_softc*,struct ecore_raw_obj*) ;int /*<<< orphan*/  (* clear_pending ) (struct ecore_raw_obj*) ;int /*<<< orphan*/  (* set_pending ) (struct ecore_raw_obj*) ;} ;
struct ecore_rss_config_obj {int (* config_rss ) (struct bxe_softc*,struct ecore_config_rss_params*) ;struct ecore_raw_obj raw; } ;
struct ecore_config_rss_params {int /*<<< orphan*/  ramrod_flags; struct ecore_rss_config_obj* rss_obj; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int /*<<< orphan*/ ) ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAMROD_COMP_WAIT ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  stub1 (struct ecore_raw_obj*) ; 
 int stub2 (struct bxe_softc*,struct ecore_config_rss_params*) ; 
 int /*<<< orphan*/  stub3 (struct ecore_raw_obj*) ; 
 int stub4 (struct bxe_softc*,struct ecore_raw_obj*) ; 

int ecore_config_rss(struct bxe_softc *sc,
		     struct ecore_config_rss_params *p)
{
	int rc;
	struct ecore_rss_config_obj *o = p->rss_obj;
	struct ecore_raw_obj *r = &o->raw;

	/* Do nothing if only driver cleanup was requested */
	if (ECORE_TEST_BIT(RAMROD_DRV_CLR_ONLY, &p->ramrod_flags)) {
		ECORE_MSG(sc, "Not configuring RSS ramrod_flags=%lx\n",
			  p->ramrod_flags);
		return ECORE_SUCCESS;
	}

	r->set_pending(r);

	rc = o->config_rss(sc, p);
	if (rc < 0) {
		r->clear_pending(r);
		return rc;
	}

	if (ECORE_TEST_BIT(RAMROD_COMP_WAIT, &p->ramrod_flags))
		rc = r->wait_comp(sc, r);

	return rc;
}