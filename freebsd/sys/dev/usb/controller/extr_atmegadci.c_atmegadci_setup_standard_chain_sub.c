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
struct atmegadci_td {int /*<<< orphan*/  alt_next; int /*<<< orphan*/  short_pkt; int /*<<< orphan*/  did_stall; scalar_t__ error; int /*<<< orphan*/  remainder; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; int /*<<< orphan*/  func; struct atmegadci_td* obj_next; } ;
struct atmegadci_std_temp {int /*<<< orphan*/  setup_alt_next; int /*<<< orphan*/  short_pkt; int /*<<< orphan*/  did_stall; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; int /*<<< orphan*/  func; struct atmegadci_td* td_next; struct atmegadci_td* td; } ;

/* Variables and functions */

__attribute__((used)) static void
atmegadci_setup_standard_chain_sub(struct atmegadci_std_temp *temp)
{
	struct atmegadci_td *td;

	/* get current Transfer Descriptor */
	td = temp->td_next;
	temp->td = td;

	/* prepare for next TD */
	temp->td_next = td->obj_next;

	/* fill out the Transfer Descriptor */
	td->func = temp->func;
	td->pc = temp->pc;
	td->offset = temp->offset;
	td->remainder = temp->len;
	td->error = 0;
	td->did_stall = temp->did_stall;
	td->short_pkt = temp->short_pkt;
	td->alt_next = temp->setup_alt_next;
}