#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ng_l2cap_cmd_p ;
typedef  TYPE_2__* ng_l2cap_chan_p ;
struct TYPE_16__ {int /*<<< orphan*/  cmd_list; } ;
struct TYPE_15__ {TYPE_6__* con; } ;
struct TYPE_14__ {int flags; TYPE_2__* ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NETGRAPH_L2CAP ; 
 int NG_L2CAP_CMD_PENDING ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 TYPE_1__* TAILQ_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ng_l2cap_command_untimeout (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_l2cap_con_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  ng_l2cap_free_cmd (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_l2cap_unlink_cmd (TYPE_1__*) ; 

void
ng_l2cap_free_chan(ng_l2cap_chan_p ch)
{
	ng_l2cap_cmd_p	f = NULL, n = NULL;

	f = TAILQ_FIRST(&ch->con->cmd_list);

	while (f != NULL) {
		n = TAILQ_NEXT(f, next);

		if (f->ch == ch) {
			ng_l2cap_unlink_cmd(f);
			if (f->flags & NG_L2CAP_CMD_PENDING)
				ng_l2cap_command_untimeout(f);
			ng_l2cap_free_cmd(f);
		}

		f = n;
	}

	LIST_REMOVE(ch, next);

	ng_l2cap_con_unref(ch->con);

	bzero(ch, sizeof(*ch));
	free(ch, M_NETGRAPH_L2CAP);
}