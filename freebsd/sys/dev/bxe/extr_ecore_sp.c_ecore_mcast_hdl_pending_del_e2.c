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
struct TYPE_2__ {scalar_t__ macs_num; } ;
struct ecore_pending_mcast_cmd {int /*<<< orphan*/  done; TYPE_1__ data; int /*<<< orphan*/  type; } ;
struct ecore_mcast_obj {int max_cmd_len; int /*<<< orphan*/  (* set_one_rule ) (struct bxe_softc*,struct ecore_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_MSG (struct bxe_softc*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  stub1 (struct bxe_softc*,struct ecore_mcast_obj*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ecore_mcast_hdl_pending_del_e2(struct bxe_softc *sc,
	struct ecore_mcast_obj *o, struct ecore_pending_mcast_cmd *cmd_pos,
	int *line_idx)
{
	int cnt = *line_idx;

	while (cmd_pos->data.macs_num) {
		o->set_one_rule(sc, o, cnt, NULL, cmd_pos->type);

		cnt++;

		cmd_pos->data.macs_num--;

		  ECORE_MSG(sc, "Deleting MAC. %d left,cnt is %d\n",
				  cmd_pos->data.macs_num, cnt);

		/* Break if we reached the maximum
		 * number of rules.
		 */
		if (cnt >= o->max_cmd_len)
			break;
	}

	*line_idx = cnt;

	/* If we cleared all bins - we are done */
	if (!cmd_pos->data.macs_num)
		cmd_pos->done = TRUE;
}