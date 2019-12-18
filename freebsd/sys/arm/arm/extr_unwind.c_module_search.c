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
struct search_context {int /*<<< orphan*/ * exidx_end; int /*<<< orphan*/ * exidx_start; scalar_t__ addr; } ;
struct TYPE_7__ {int /*<<< orphan*/ * value; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  TYPE_2__* linker_file_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;
struct TYPE_8__ {scalar_t__ address; scalar_t__ size; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 scalar_t__ LINKER_LOOKUP_SYMBOL (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ LINKER_SYMBOL_VALUES (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
module_search(linker_file_t lf, void *context)
{
	struct search_context *sc = context;
	linker_symval_t symval;
	c_linker_sym_t sym;

	if (lf->address <= (caddr_t)sc->addr &&
	    (lf->address + lf->size) >= (caddr_t)sc->addr) {
		if ((LINKER_LOOKUP_SYMBOL(lf, "__exidx_start", &sym) == 0 ||
		    LINKER_LOOKUP_SYMBOL(lf, "exidx_start", &sym) == 0) &&
		    LINKER_SYMBOL_VALUES(lf, sym, &symval) == 0)
			sc->exidx_start = symval.value;

		if ((LINKER_LOOKUP_SYMBOL(lf, "__exidx_end", &sym) == 0 ||
		    LINKER_LOOKUP_SYMBOL(lf, "exidx_end", &sym) == 0) &&
		    LINKER_SYMBOL_VALUES(lf, sym, &symval) == 0)
			sc->exidx_end = symval.value;

		if (sc->exidx_start != NULL && sc->exidx_end != NULL)
			return (1);
		panic("Invalid module %s, no unwind tables\n", lf->filename);
	}
	return (0);
}