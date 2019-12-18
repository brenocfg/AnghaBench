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
struct macro_definition {int dummy; } ;
typedef  TYPE_1__* ndptr ;
struct TYPE_3__ {struct macro_definition* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  macros ; 
 TYPE_1__* ohash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohash_qlookup (int /*<<< orphan*/ *,char const*) ; 

struct macro_definition *
lookup_macro_definition(const char *name)
{
	ndptr p;

	p = ohash_find(&macros, ohash_qlookup(&macros, name));
	if (p)
		return p->d;
	else
		return NULL;
}