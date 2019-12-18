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
struct partial_symtab {int /*<<< orphan*/  n_global_syms; scalar_t__ globals_offset; TYPE_2__* objfile; } ;
struct partial_symbol {int dummy; } ;
struct TYPE_3__ {scalar_t__ list; } ;
struct TYPE_4__ {TYPE_1__ global_psymbols; } ;

/* Variables and functions */
 int /*<<< orphan*/  compare_psymbols ; 
 int /*<<< orphan*/  qsort (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
sort_pst_symbols (struct partial_symtab *pst)
{
  /* Sort the global list; don't sort the static list */

  qsort (pst->objfile->global_psymbols.list + pst->globals_offset,
	 pst->n_global_syms, sizeof (struct partial_symbol *),
	 compare_psymbols);
}