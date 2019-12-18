#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rl_command_func_t ;
struct TYPE_3__ {int /*<<< orphan*/ * key; } ;
struct TYPE_4__ {TYPE_1__ el_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED_INSERT ; 
 TYPE_2__* e ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  rl_initialize () ; 
 int /*<<< orphan*/ * rl_insert ; 

int
rl_bind_key(int c, rl_command_func_t *func)
{
	int retval = -1;

	if (h == NULL || e == NULL)
		rl_initialize();

	if (func == rl_insert) {
		/* XXX notice there is no range checking of ``c'' */
		e->el_map.key[c] = ED_INSERT;
		retval = 0;
	}
	return retval;
}