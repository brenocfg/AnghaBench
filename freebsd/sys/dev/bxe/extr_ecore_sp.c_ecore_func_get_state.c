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
struct ecore_func_sp_obj {int state; scalar_t__ pending; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_func_state { ____Placeholder_ecore_func_state } ecore_func_state ;

/* Variables and functions */
 int ECORE_F_STATE_MAX ; 
 int /*<<< orphan*/  rmb () ; 

enum ecore_func_state ecore_func_get_state(struct bxe_softc *sc,
					   struct ecore_func_sp_obj *o)
{
	/* in the middle of transaction - return INVALID state */
	if (o->pending)
		return ECORE_F_STATE_MAX;

	/* unsure the order of reading of o->pending and o->state
	 * o->pending should be read first
	 */
	rmb();

	return o->state;
}