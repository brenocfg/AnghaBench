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
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  kvaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kgdb_resolve_symbol(const char *name, kvaddr_t *kva)
{
	struct minimal_symbol *ms;

	ms = lookup_minimal_symbol (name, NULL, NULL);
	if (ms == NULL)
		return (1);

	*kva = SYMBOL_VALUE_ADDRESS (ms);
	return (0);
}