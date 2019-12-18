#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct block {int sense; int /*<<< orphan*/  head; } ;
struct TYPE_7__ {int /*<<< orphan*/  root; } ;
struct TYPE_8__ {TYPE_1__ ic; int /*<<< orphan*/  snaplen; } ;
typedef  TYPE_2__ compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  backpatch (struct block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_ppi_dlt_check (TYPE_2__*) ; 
 int /*<<< orphan*/  gen_retblk (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_compute_vloffsets (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
finish_parse(compiler_state_t *cstate, struct block *p)
{
	struct block *ppi_dlt_check;

	/*
	 * Insert before the statements of the first (root) block any
	 * statements needed to load the lengths of any variable-length
	 * headers into registers.
	 *
	 * XXX - a fancier strategy would be to insert those before the
	 * statements of all blocks that use those lengths and that
	 * have no predecessors that use them, so that we only compute
	 * the lengths if we need them.  There might be even better
	 * approaches than that.
	 *
	 * However, those strategies would be more complicated, and
	 * as we don't generate code to compute a length if the
	 * program has no tests that use the length, and as most
	 * tests will probably use those lengths, we would just
	 * postpone computing the lengths so that it's not done
	 * for tests that fail early, and it's not clear that's
	 * worth the effort.
	 */
	insert_compute_vloffsets(cstate, p->head);

	/*
	 * For DLT_PPI captures, generate a check of the per-packet
	 * DLT value to make sure it's DLT_IEEE802_11.
	 *
	 * XXX - TurboCap cards use DLT_PPI for Ethernet.
	 * Can we just define some DLT_ETHERNET_WITH_PHDR pseudo-header
	 * with appropriate Ethernet information and use that rather
	 * than using something such as DLT_PPI where you don't know
	 * the link-layer header type until runtime, which, in the
	 * general case, would force us to generate both Ethernet *and*
	 * 802.11 code (*and* anything else for which PPI is used)
	 * and choose between them early in the BPF program?
	 */
	ppi_dlt_check = gen_ppi_dlt_check(cstate);
	if (ppi_dlt_check != NULL)
		gen_and(ppi_dlt_check, p);

	backpatch(p, gen_retblk(cstate, cstate->snaplen));
	p->sense = !p->sense;
	backpatch(p, gen_retblk(cstate, 0));
	cstate->ic.root = p->head;
}