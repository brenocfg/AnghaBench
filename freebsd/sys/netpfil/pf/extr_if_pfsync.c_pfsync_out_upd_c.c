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
struct pfsync_upd_c {int /*<<< orphan*/  timeout; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  id; } ;
struct pf_state {int /*<<< orphan*/  timeout; int /*<<< orphan*/  creatorid; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct pfsync_upd_c*,int) ; 
 int /*<<< orphan*/  pf_state_peer_hton (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pfsync_out_upd_c(struct pf_state *st, void *buf)
{
	struct pfsync_upd_c *up = buf;

	bzero(up, sizeof(*up));
	up->id = st->id;
	pf_state_peer_hton(&st->src, &up->src);
	pf_state_peer_hton(&st->dst, &up->dst);
	up->creatorid = st->creatorid;
	up->timeout = st->timeout;
}