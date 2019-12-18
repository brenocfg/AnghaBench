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
typedef  int /*<<< orphan*/  u_short ;
struct peer {int flags; int cast_flags; int /*<<< orphan*/  last_event; int /*<<< orphan*/  num_events; scalar_t__ reach; scalar_t__ keyid; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_PEER_STATUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTL_PST_AUTHENABLE ; 
 int /*<<< orphan*/  CTL_PST_AUTHENTIC ; 
 int /*<<< orphan*/  CTL_PST_BCAST ; 
 int /*<<< orphan*/  CTL_PST_CONFIG ; 
 int /*<<< orphan*/  CTL_PST_REACH ; 
 int FLAG_AUTHENTIC ; 
 int FLAG_CONFIG ; 
 int MDF_TXONLY_MASK ; 

u_short
ctlpeerstatus(
	register struct peer *p
	)
{
	u_short status;

	status = p->status;
	if (FLAG_CONFIG & p->flags)
		status |= CTL_PST_CONFIG;
	if (p->keyid)
		status |= CTL_PST_AUTHENABLE;
	if (FLAG_AUTHENTIC & p->flags)
		status |= CTL_PST_AUTHENTIC;
	if (p->reach)
		status |= CTL_PST_REACH;
	if (MDF_TXONLY_MASK & p->cast_flags)
		status |= CTL_PST_BCAST;

	return CTL_PEER_STATUS(status, p->num_events, p->last_event);
}