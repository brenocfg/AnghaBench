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
struct mesh_state {struct mesh_state* unique; } ;

/* Variables and functions */

void
mesh_state_make_unique(struct mesh_state* mstate)
{
	mstate->unique = mstate;
}