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
struct iwm_softc {int dummy; } ;
struct iwm_phy_db {int n_group_txp; int n_group_papd; struct iwm_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct iwm_phy_db* malloc (int,int /*<<< orphan*/ ,int) ; 

struct iwm_phy_db *
iwm_phy_db_init(struct iwm_softc *sc)
{
	struct iwm_phy_db *phy_db = malloc(sizeof(struct iwm_phy_db),
	    M_DEVBUF, M_NOWAIT | M_ZERO);

	if (!phy_db)
		return phy_db;

	phy_db->sc = sc;

	phy_db->n_group_txp = -1;
	phy_db->n_group_papd = -1;

	/* TODO: add default values of the phy db. */
	return phy_db;
}