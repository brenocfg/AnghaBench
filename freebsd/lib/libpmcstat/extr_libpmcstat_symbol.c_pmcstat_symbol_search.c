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
typedef  void* uintfptr_t ;
struct pmcstat_symbol {void* ps_end; void* ps_start; int /*<<< orphan*/ * ps_name; } ;
struct pmcstat_image {int /*<<< orphan*/  pi_symcount; int /*<<< orphan*/ * pi_symbols; } ;

/* Variables and functions */
 struct pmcstat_symbol* bsearch (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcstat_symbol_compare ; 

struct pmcstat_symbol *
pmcstat_symbol_search(struct pmcstat_image *image, uintfptr_t addr)
{
	struct pmcstat_symbol sym;

	if (image->pi_symbols == NULL)
		return (NULL);

	sym.ps_name  = NULL;
	sym.ps_start = addr;
	sym.ps_end   = addr + 1;

	return (bsearch((void *) &sym, image->pi_symbols,
	    image->pi_symcount, sizeof(struct pmcstat_symbol),
	    pmcstat_symbol_compare));
}