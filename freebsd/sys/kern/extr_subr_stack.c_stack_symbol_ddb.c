#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ linker_ddb_search_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long*) ; 
 scalar_t__ linker_ddb_symbol_values (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
stack_symbol_ddb(vm_offset_t pc, const char **name, long *offset)
{
	linker_symval_t symval;
	c_linker_sym_t sym;

	if (linker_ddb_search_symbol((caddr_t)pc, &sym, offset) != 0)
		goto out;
	if (linker_ddb_symbol_values(sym, &symval) != 0)
		goto out;
	if (symval.name != NULL) {
		*name = symval.name;
		return (0);
	}
 out:
	*offset = 0;
	*name = "??";
	return (ENOENT);
}