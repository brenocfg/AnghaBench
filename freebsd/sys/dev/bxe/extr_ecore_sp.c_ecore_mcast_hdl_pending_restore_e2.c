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
struct TYPE_2__ {scalar_t__ next_bin; } ;
struct ecore_pending_mcast_cmd {TYPE_1__ data; int /*<<< orphan*/  done; } ;
struct ecore_mcast_obj {scalar_t__ (* hdl_restore ) (struct bxe_softc*,struct ecore_mcast_obj*,scalar_t__,int*) ;} ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ stub1 (struct bxe_softc*,struct ecore_mcast_obj*,scalar_t__,int*) ; 

__attribute__((used)) static inline void ecore_mcast_hdl_pending_restore_e2(struct bxe_softc *sc,
	struct ecore_mcast_obj *o, struct ecore_pending_mcast_cmd *cmd_pos,
	int *line_idx)
{
	cmd_pos->data.next_bin = o->hdl_restore(sc, o, cmd_pos->data.next_bin,
						line_idx);

	if (cmd_pos->data.next_bin < 0)
		/* If o->set_restore returned -1 we are done */
		cmd_pos->done = TRUE;
	else
		/* Start from the next bin next time */
		cmd_pos->data.next_bin++;
}