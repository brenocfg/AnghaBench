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
struct ecore_func_sp_obj {unsigned long pending; int /*<<< orphan*/  next_state; int /*<<< orphan*/  state; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_func_cmd { ____Placeholder_ecore_func_cmd } ecore_func_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CLEAR_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_FUNC_ID (struct bxe_softc*) ; 
 int /*<<< orphan*/  ECORE_F_STATE_MAX ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECORE_SMP_MB_AFTER_CLEAR_BIT () ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ECORE_TEST_AND_CLEAR_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline int ecore_func_state_change_comp(struct bxe_softc *sc,
					       struct ecore_func_sp_obj *o,
					       enum ecore_func_cmd cmd)
{
	unsigned long cur_pending = o->pending;

	if (!ECORE_TEST_AND_CLEAR_BIT(cmd, &cur_pending)) {
		ECORE_ERR("Bad MC reply %d for func %d in state %d pending 0x%lx, next_state %d\n",
			  cmd, ECORE_FUNC_ID(sc), o->state,
			  cur_pending, o->next_state);
		return ECORE_INVAL;
	}

	ECORE_MSG(sc,
		  "Completing command %d for func %d, setting state to %d\n",
		  cmd, ECORE_FUNC_ID(sc), o->next_state);

	o->state = o->next_state;
	o->next_state = ECORE_F_STATE_MAX;

	/* It's important that o->state and o->next_state are
	 * updated before o->pending.
	 */
	wmb();

	ECORE_CLEAR_BIT(cmd, &o->pending);
	ECORE_SMP_MB_AFTER_CLEAR_BIT();

	return ECORE_SUCCESS;
}