#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct pg_state {unsigned int level; scalar_t__ current_flags; unsigned long start_address; scalar_t__ start_pa; scalar_t__ last_pa; TYPE_1__* marker; int /*<<< orphan*/  seq; } ;
struct TYPE_4__ {scalar_t__ mask; int /*<<< orphan*/  num; scalar_t__ flag; } ;
struct TYPE_3__ {unsigned long start_address; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PTE_RPN_MASK ; 
 int /*<<< orphan*/  dump_addr (struct pg_state*,unsigned long) ; 
 int /*<<< orphan*/  dump_flag_info (struct pg_state*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  note_prot_wx (struct pg_state*,unsigned long) ; 
 TYPE_2__* pg_level ; 
 int /*<<< orphan*/  pt_dump_seq_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_dump_seq_putc (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void note_page(struct pg_state *st, unsigned long addr,
	       unsigned int level, u64 val)
{
	u64 flag = val & pg_level[level].mask;
	u64 pa = val & PTE_RPN_MASK;

	/* At first no level is set */
	if (!st->level) {
		st->level = level;
		st->current_flags = flag;
		st->start_address = addr;
		st->start_pa = pa;
		st->last_pa = pa;
		pt_dump_seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
	/*
	 * Dump the section of virtual memory when:
	 *   - the PTE flags from one entry to the next differs.
	 *   - we change levels in the tree.
	 *   - the address is in a different section of memory and is thus
	 *   used for a different purpose, regardless of the flags.
	 *   - the pa of this page is not adjacent to the last inspected page
	 */
	} else if (flag != st->current_flags || level != st->level ||
		   addr >= st->marker[1].start_address ||
		   (pa != st->last_pa + PAGE_SIZE &&
		    (pa != st->start_pa || st->start_pa != st->last_pa))) {

		/* Check the PTE flags */
		if (st->current_flags) {
			note_prot_wx(st, addr);
			dump_addr(st, addr);

			/* Dump all the flags */
			if (pg_level[st->level].flag)
				dump_flag_info(st, pg_level[st->level].flag,
					  st->current_flags,
					  pg_level[st->level].num);

			pt_dump_seq_putc(st->seq, '\n');
		}

		/*
		 * Address indicates we have passed the end of the
		 * current section of virtual memory
		 */
		while (addr >= st->marker[1].start_address) {
			st->marker++;
			pt_dump_seq_printf(st->seq, "---[ %s ]---\n", st->marker->name);
		}
		st->start_address = addr;
		st->start_pa = pa;
		st->last_pa = pa;
		st->current_flags = flag;
		st->level = level;
	} else {
		st->last_pa = pa;
	}
}