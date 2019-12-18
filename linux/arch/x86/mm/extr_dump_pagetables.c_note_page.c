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
struct seq_file {int dummy; } ;
struct pg_state {void* current_prot; scalar_t__ effective_prot; int level; scalar_t__ lines; scalar_t__ current_address; unsigned long start_address; TYPE_1__* marker; int /*<<< orphan*/  to_dmesg; scalar_t__ check_wx; } ;
typedef  scalar_t__ pgprotval_t ;
typedef  void* pgprot_t ;
struct TYPE_2__ {scalar_t__ start_address; scalar_t__ max_lines; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ _PAGE_NX ; 
 scalar_t__ _PAGE_RW ; 
 TYPE_1__* address_markers ; 
 int /*<<< orphan*/  note_wx (struct pg_state*) ; 
 scalar_t__ pgprot_val (void*) ; 
 int /*<<< orphan*/  printk_prot (struct seq_file*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_dump_cont_printf (struct seq_file*,int /*<<< orphan*/ ,char*,unsigned long,char const) ; 
 int /*<<< orphan*/  pt_dump_seq_printf (struct seq_file*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void note_page(struct seq_file *m, struct pg_state *st,
		      pgprot_t new_prot, pgprotval_t new_eff, int level)
{
	pgprotval_t prot, cur, eff;
	static const char units[] = "BKMGTPE";

	/*
	 * If we have a "break" in the series, we need to flush the state that
	 * we have now. "break" is either changing perms, levels or
	 * address space marker.
	 */
	prot = pgprot_val(new_prot);
	cur = pgprot_val(st->current_prot);
	eff = st->effective_prot;

	if (!st->level) {
		/* First entry */
		st->current_prot = new_prot;
		st->effective_prot = new_eff;
		st->level = level;
		st->marker = address_markers;
		st->lines = 0;
		pt_dump_seq_printf(m, st->to_dmesg, "---[ %s ]---\n",
				   st->marker->name);
	} else if (prot != cur || new_eff != eff || level != st->level ||
		   st->current_address >= st->marker[1].start_address) {
		const char *unit = units;
		unsigned long delta;
		int width = sizeof(unsigned long) * 2;

		if (st->check_wx && (eff & _PAGE_RW) && !(eff & _PAGE_NX))
			note_wx(st);

		/*
		 * Now print the actual finished series
		 */
		if (!st->marker->max_lines ||
		    st->lines < st->marker->max_lines) {
			pt_dump_seq_printf(m, st->to_dmesg,
					   "0x%0*lx-0x%0*lx   ",
					   width, st->start_address,
					   width, st->current_address);

			delta = st->current_address - st->start_address;
			while (!(delta & 1023) && unit[1]) {
				delta >>= 10;
				unit++;
			}
			pt_dump_cont_printf(m, st->to_dmesg, "%9lu%c ",
					    delta, *unit);
			printk_prot(m, st->current_prot, st->level,
				    st->to_dmesg);
		}
		st->lines++;

		/*
		 * We print markers for special areas of address space,
		 * such as the start of vmalloc space etc.
		 * This helps in the interpretation.
		 */
		if (st->current_address >= st->marker[1].start_address) {
			if (st->marker->max_lines &&
			    st->lines > st->marker->max_lines) {
				unsigned long nskip =
					st->lines - st->marker->max_lines;
				pt_dump_seq_printf(m, st->to_dmesg,
						   "... %lu entr%s skipped ... \n",
						   nskip,
						   nskip == 1 ? "y" : "ies");
			}
			st->marker++;
			st->lines = 0;
			pt_dump_seq_printf(m, st->to_dmesg, "---[ %s ]---\n",
					   st->marker->name);
		}

		st->start_address = st->current_address;
		st->current_prot = new_prot;
		st->effective_prot = new_eff;
		st->level = level;
	}
}