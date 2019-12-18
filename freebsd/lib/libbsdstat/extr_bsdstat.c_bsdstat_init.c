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
struct fmt {int dummy; } ;
struct bsdstat {char const* name; int nstats; int /*<<< orphan*/  print_fields; int /*<<< orphan*/  print_verbose; int /*<<< orphan*/  print_total; int /*<<< orphan*/  print_current; int /*<<< orphan*/  print_header; void* get_totstat; void* get_curstat; int /*<<< orphan*/  update_tot; void* collect_tot; void* collect_cur; int /*<<< orphan*/  setfmt; struct fmt const* stats; } ;

/* Variables and functions */
 void* bsdstat_collect ; 
 void* bsdstat_get ; 
 int /*<<< orphan*/  bsdstat_print_current ; 
 int /*<<< orphan*/  bsdstat_print_fields ; 
 int /*<<< orphan*/  bsdstat_print_header ; 
 int /*<<< orphan*/  bsdstat_print_total ; 
 int /*<<< orphan*/  bsdstat_print_verbose ; 
 int /*<<< orphan*/  bsdstat_setfmt ; 
 int /*<<< orphan*/  bsdstat_update_tot ; 

void
bsdstat_init(struct bsdstat *sf, const char *name, const struct fmt *stats, int nstats)
{
	sf->name = name;
	sf->stats = stats;
	sf->nstats = nstats;
	sf->setfmt = bsdstat_setfmt;
	sf->collect_cur = bsdstat_collect;
	sf->collect_tot = bsdstat_collect;
	sf->update_tot = bsdstat_update_tot;
	sf->get_curstat = bsdstat_get;
	sf->get_totstat = bsdstat_get;
	sf->print_header = bsdstat_print_header;
	sf->print_current = bsdstat_print_current;
	sf->print_total = bsdstat_print_total;
	sf->print_verbose = bsdstat_print_verbose;
	sf->print_fields = bsdstat_print_fields;
}