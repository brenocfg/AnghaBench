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
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_CMDQ_LOCK_DESTROY (struct rtwn_softc*) ; 
 scalar_t__ RTWN_CMDQ_LOCK_INITIALIZED (struct rtwn_softc*) ; 

void
rtwn_cmdq_destroy(struct rtwn_softc *sc)
{
	if (RTWN_CMDQ_LOCK_INITIALIZED(sc))
		RTWN_CMDQ_LOCK_DESTROY(sc);
}