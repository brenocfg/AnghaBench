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
struct rtwn_softc {struct r12a_softc* sc_priv; } ;
struct r12a_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_RTWN_PRIV ; 
 int /*<<< orphan*/  free (struct r12a_softc*,int /*<<< orphan*/ ) ; 

void
r12a_detach_private(struct rtwn_softc *sc)
{
	struct r12a_softc *rs = sc->sc_priv;

	free(rs, M_RTWN_PRIV);
}