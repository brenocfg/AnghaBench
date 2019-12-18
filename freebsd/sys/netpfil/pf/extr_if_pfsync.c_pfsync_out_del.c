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
struct pfsync_del_c {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;
struct pf_state {int /*<<< orphan*/  state_flags; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFSTATE_NOSYNC ; 

__attribute__((used)) static void
pfsync_out_del(struct pf_state *st, void *buf)
{
	struct pfsync_del_c *dp = buf;

	dp->id = st->id;
	dp->creatorid = st->creatorid;
	st->state_flags |= PFSTATE_NOSYNC;
}