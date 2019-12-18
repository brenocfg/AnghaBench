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
struct rsu_softc {int /*<<< orphan*/  sc_tx_inactive; } ;
struct rsu_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSU_ASSERT_LOCKED (struct rsu_softc*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct rsu_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static void
rsu_freebuf(struct rsu_softc *sc, struct rsu_data *bf)
{

	RSU_ASSERT_LOCKED(sc);
	STAILQ_INSERT_TAIL(&sc->sc_tx_inactive, bf, next);
}