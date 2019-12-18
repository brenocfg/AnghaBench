#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ndptr ;
struct TYPE_6__ {int /*<<< orphan*/ * d; int /*<<< orphan*/  builtin_type; int /*<<< orphan*/  trace_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_NO_TRACE ; 
 int /*<<< orphan*/  MACRTYPE ; 
 int /*<<< orphan*/  macro_info ; 
 int /*<<< orphan*/  macros ; 
 TYPE_1__* ohash_create_entry (int /*<<< orphan*/ *,char const*,char const**) ; 
 TYPE_1__* ohash_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ohash_insert (int /*<<< orphan*/ *,unsigned int,TYPE_1__*) ; 
 unsigned int ohash_qlookupi (int /*<<< orphan*/ *,char const*,char const**) ; 

__attribute__((used)) static ndptr
create_entry(const char *name)
{
	const char *end = NULL;
	unsigned int i;
	ndptr n;

	i = ohash_qlookupi(&macros, name, &end);
	n = ohash_find(&macros, i);
	if (n == NULL) {
		n = ohash_create_entry(&macro_info, name, &end);
		ohash_insert(&macros, i, n);
		n->trace_flags = FLAG_NO_TRACE;
		n->builtin_type = MACRTYPE;
		n->d = NULL;
	}
	return n;
}