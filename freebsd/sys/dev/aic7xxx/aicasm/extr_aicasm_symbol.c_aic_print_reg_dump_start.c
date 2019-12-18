#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* symbol; } ;
typedef  TYPE_2__ symbol_node_t ;
struct TYPE_4__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 char* prefix ; 

__attribute__((used)) static void
aic_print_reg_dump_start(FILE *dfile, symbol_node_t *regnode)
{
	if (dfile == NULL)
		return;

	fprintf(dfile,
"static %sreg_parse_entry_t %s_parse_table[] = {\n",
		prefix,
		regnode->symbol->name);
}