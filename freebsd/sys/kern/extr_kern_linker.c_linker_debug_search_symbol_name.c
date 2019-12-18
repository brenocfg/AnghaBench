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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;

/* Variables and functions */
 int linker_debug_search_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long*) ; 
 int linker_debug_symbol_values (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linker_debug_search_symbol_name(caddr_t value, char *buf, u_int buflen,
    long *offset)
{
	linker_symval_t symval;
	c_linker_sym_t sym;
	int error;

	*offset = 0;
	error = linker_debug_search_symbol(value, &sym, offset);
	if (error)
		return (error);
	error = linker_debug_symbol_values(sym, &symval);
	if (error)
		return (error);
	strlcpy(buf, symval.name, buflen);
	return (0);
}