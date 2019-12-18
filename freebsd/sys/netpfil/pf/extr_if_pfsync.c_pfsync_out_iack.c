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
struct pfsync_ins_ack {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;
struct pf_state {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;

/* Variables and functions */

__attribute__((used)) static void
pfsync_out_iack(struct pf_state *st, void *buf)
{
	struct pfsync_ins_ack *iack = buf;

	iack->id = st->id;
	iack->creatorid = st->creatorid;
}