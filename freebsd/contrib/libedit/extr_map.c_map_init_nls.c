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
typedef  int /*<<< orphan*/  el_action_t ;
struct TYPE_4__ {int /*<<< orphan*/ * key; } ;
struct TYPE_5__ {TYPE_1__ el_map; } ;
typedef  TYPE_2__ EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  ED_INSERT ; 
 scalar_t__ iswprint (int) ; 

__attribute__((used)) static void
map_init_nls(EditLine *el)
{
	int i;

	el_action_t *map = el->el_map.key;

	for (i = 0200; i <= 0377; i++)
		if (iswprint(i))
			map[i] = ED_INSERT;
}