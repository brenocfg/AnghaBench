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
struct TYPE_3__ {scalar_t__ blocks; scalar_t__ levels; scalar_t__ space; scalar_t__ edges; scalar_t__ vmap; scalar_t__ vnode_base; } ;
typedef  TYPE_1__ opt_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void
opt_cleanup(opt_state_t *opt_state)
{
	free((void *)opt_state->vnode_base);
	free((void *)opt_state->vmap);
	free((void *)opt_state->edges);
	free((void *)opt_state->space);
	free((void *)opt_state->levels);
	free((void *)opt_state->blocks);
}