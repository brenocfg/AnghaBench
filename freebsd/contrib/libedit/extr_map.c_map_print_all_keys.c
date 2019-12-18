#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* key; scalar_t__* alt; } ;
struct TYPE_8__ {int /*<<< orphan*/  el_outfile; TYPE_1__ el_map; } ;
typedef  TYPE_2__ EditLine ;

/* Variables and functions */
 int N_KEYS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  keymacro_print (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  map_print_some_keys (TYPE_2__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  terminal_print_arrow (TYPE_2__*,char*) ; 

__attribute__((used)) static void
map_print_all_keys(EditLine *el)
{
	int prev, i;

	(void) fprintf(el->el_outfile, "Standard key bindings\n");
	prev = 0;
	for (i = 0; i < N_KEYS; i++) {
		if (el->el_map.key[prev] == el->el_map.key[i])
			continue;
		map_print_some_keys(el, el->el_map.key, prev, i - 1);
		prev = i;
	}
	map_print_some_keys(el, el->el_map.key, prev, i - 1);

	(void) fprintf(el->el_outfile, "Alternative key bindings\n");
	prev = 0;
	for (i = 0; i < N_KEYS; i++) {
		if (el->el_map.alt[prev] == el->el_map.alt[i])
			continue;
		map_print_some_keys(el, el->el_map.alt, prev, i - 1);
		prev = i;
	}
	map_print_some_keys(el, el->el_map.alt, prev, i - 1);

	(void) fprintf(el->el_outfile, "Multi-character bindings\n");
	keymacro_print(el, L"");
	(void) fprintf(el->el_outfile, "Arrow key bindings\n");
	terminal_print_arrow(el, L"");
}