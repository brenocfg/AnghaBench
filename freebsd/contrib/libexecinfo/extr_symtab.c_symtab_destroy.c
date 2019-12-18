#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t nsymbols; struct TYPE_4__* symbols; struct TYPE_4__* st_name; } ;
typedef  TYPE_1__ symtab_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
symtab_destroy(symtab_t *s)
{
	if (s == NULL)
		return;
	for (size_t i = 0; i < s->nsymbols; i++)
		free(s->symbols[i].st_name);
	free(s->symbols);
	free(s);
}