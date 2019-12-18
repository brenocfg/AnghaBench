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
struct TYPE_3__ {scalar_t__ value; } ;
typedef  TYPE_1__ linker_symval_t ;
typedef  void* linker_file_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCOV_PREFIX ; 
 int /*<<< orphan*/  LINKER_LOOKUP_SYMBOL (void*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LINKER_SYMBOL_VALUES (void*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * strstr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gcov_invoke_ctor(const char *name, void *arg)
{
	void (*ctor)(void);
	c_linker_sym_t sym;
	linker_symval_t symval;
	linker_file_t lf;

	if (strstr(name, GCOV_PREFIX) == NULL)
		return (0);
	lf = arg;
	LINKER_LOOKUP_SYMBOL(lf, name, &sym);
	LINKER_SYMBOL_VALUES(lf, sym, &symval);
	ctor = (void *)symval.value;
	ctor();
	return (0);
}