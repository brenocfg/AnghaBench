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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kgdb_parse (char*) ; 

CORE_ADDR
kgdb_lookup(const char *sym)
{
	CORE_ADDR addr;
	char *name;

	asprintf(&name, "&%s", sym);
	addr = kgdb_parse(name);
	free(name);
	return (addr);
}