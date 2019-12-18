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
 int /*<<< orphan*/  db_add_symbol_table (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  db_command_init () ; 
 scalar_t__ kstrtab ; 
 scalar_t__ ksymtab ; 
 scalar_t__ ksymtab_size ; 

__attribute__((used)) static int
db_init(void)
{

	db_command_init();

	if (ksymtab != 0 && kstrtab != 0 && ksymtab_size != 0) {
		db_add_symbol_table((char *)ksymtab,
		    (char *)(ksymtab + ksymtab_size), "elf", (char *)kstrtab);
	}
	db_add_symbol_table(NULL, NULL, "kld", NULL);
	return (1);	/* We're the default debugger. */
}