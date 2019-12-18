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
struct ecore_queue_sp_obj {unsigned long pending; scalar_t__ next_tx_only; scalar_t__ max_cos; scalar_t__ num_tx_only; int /*<<< orphan*/  next_state; int /*<<< orphan*/  state; int /*<<< orphan*/ * cids; } ;
struct bxe_softc {int dummy; } ;
typedef  enum ecore_queue_cmd { ____Placeholder_ecore_queue_cmd } ecore_queue_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CLEAR_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  ECORE_ERR (char*,scalar_t__,scalar_t__,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,int,scalar_t__,...) ; 
 size_t ECORE_PRIMARY_CID_INDEX ; 
 int /*<<< orphan*/  ECORE_Q_STATE_MAX ; 
 int /*<<< orphan*/  ECORE_SMP_MB_AFTER_CLEAR_BIT () ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ECORE_TEST_AND_CLEAR_BIT (int,unsigned long*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int ecore_queue_comp_cmd(struct bxe_softc *sc,
				struct ecore_queue_sp_obj *o,
				enum ecore_queue_cmd cmd)
{
	unsigned long cur_pending = o->pending;

	if (!ECORE_TEST_AND_CLEAR_BIT(cmd, &cur_pending)) {
		ECORE_ERR("Bad MC reply %d for queue %d in state %d pending 0x%lx, next_state %d\n",
			  cmd, o->cids[ECORE_PRIMARY_CID_INDEX],
			  o->state, cur_pending, o->next_state);
		return ECORE_INVAL;
	}

	if (o->next_tx_only >= o->max_cos)
		/* >= because tx only must always be smaller than cos since the
		 * primary connection supports COS 0
		 */
		ECORE_ERR("illegal value for next tx_only: %d. max cos was %d",
			  o->next_tx_only, o->max_cos);

	ECORE_MSG(sc,
		  "Completing command %d for queue %d, setting state to %d\n",
		  cmd, o->cids[ECORE_PRIMARY_CID_INDEX], o->next_state);

	if (o->next_tx_only)  /* print num tx-only if any exist */
		ECORE_MSG(sc, "primary cid %d: num tx-only cons %d\n",
			  o->cids[ECORE_PRIMARY_CID_INDEX], o->next_tx_only);

	o->state = o->next_state;
	o->num_tx_only = o->next_tx_only;
	o->next_state = ECORE_Q_STATE_MAX;

	/* It's important that o->state and o->next_state are
	 * updated before o->pending.
	 */
	wmb();

	ECORE_CLEAR_BIT(cmd, &o->pending);
	ECORE_SMP_MB_AFTER_CLEAR_BIT();

	return ECORE_SUCCESS;
}