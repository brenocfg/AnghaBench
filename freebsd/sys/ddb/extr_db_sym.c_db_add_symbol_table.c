#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* start; char* end; char* name; char* private; } ;

/* Variables and functions */
 size_t MAXNOSYMTABS ; 
 size_t db_nsymtab ; 
 TYPE_1__* db_symtabs ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void
db_add_symbol_table(char *start, char *end, char *name, char *ref)
{
	if (db_nsymtab >= MAXNOSYMTABS) {
		printf ("No slots left for %s symbol table", name);
		panic ("db_sym.c: db_add_symbol_table");
	}

	db_symtabs[db_nsymtab].start = start;
	db_symtabs[db_nsymtab].end = end;
	db_symtabs[db_nsymtab].name = name;
	db_symtabs[db_nsymtab].private = ref;
	db_nsymtab++;
}