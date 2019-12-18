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
struct ntb_net_queue {int /*<<< orphan*/  ifp; int /*<<< orphan*/  qp; } ;
typedef  enum ntb_link_event { ____Placeholder_ntb_link_event } ntb_link_event ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 int NTB_LINK_UP ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setbaudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_transport_link_speed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_net_event_handler(void *data, enum ntb_link_event status)
{
	struct ntb_net_queue *q = data;

	if_setbaudrate(q->ifp, ntb_transport_link_speed(q->qp));
	if_link_state_change(q->ifp, (status == NTB_LINK_UP) ? LINK_STATE_UP :
	    LINK_STATE_DOWN);
}