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

/* Variables and functions */
 int /*<<< orphan*/  dump_sym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * sym_base ; 
 unsigned long sym_count ; 
 char* sym_name (unsigned long) ; 
 scalar_t__* sym_used ; 

__attribute__((used)) static void
dump_syms(void)
{
    unsigned long i;

    printf("  Symbols:\n");
    for (i = 0;  i < sym_count;  ++i) {
	printf("    %6lu%c ", i, sym_used[i] ? '*' : ' ');
	dump_sym(&sym_base[i]);
	printf(" %s\n", sym_name(i));
    }
}