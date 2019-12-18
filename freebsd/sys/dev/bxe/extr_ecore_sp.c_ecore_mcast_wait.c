#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ (* wait_comp ) (struct bxe_softc*,TYPE_1__*) ;int /*<<< orphan*/  pstate; } ;
struct ecore_mcast_obj {TYPE_1__ raw; int /*<<< orphan*/  sched_state; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_SUCCESS ; 
 int ECORE_TIMEOUT ; 
 scalar_t__ ecore_state_wait (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct bxe_softc*,TYPE_1__*) ; 

__attribute__((used)) static int ecore_mcast_wait(struct bxe_softc *sc,
			    struct ecore_mcast_obj *o)
{
	if (ecore_state_wait(sc, o->sched_state, o->raw.pstate) ||
			o->raw.wait_comp(sc, &o->raw))
		return ECORE_TIMEOUT;

	return ECORE_SUCCESS;
}