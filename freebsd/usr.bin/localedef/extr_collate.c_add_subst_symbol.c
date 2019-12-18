#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ref; } ;
typedef  TYPE_1__ collundef_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_subst_pri (int /*<<< orphan*/ ) ; 
 size_t curr_weight ; 
 TYPE_1__* get_collundef (char*) ; 

void
add_subst_symbol(char *ptr)
{
	collundef_t *cu;

	if ((cu = get_collundef(ptr)) != NULL) {
		add_subst_pri(cu->ref[curr_weight]);
	}
}