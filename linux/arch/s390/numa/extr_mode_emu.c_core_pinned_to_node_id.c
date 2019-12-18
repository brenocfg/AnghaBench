#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct toptree {size_t id; } ;
struct TYPE_2__ {int* to_node_id; } ;

/* Variables and functions */
 TYPE_1__* emu_cores ; 

__attribute__((used)) static int core_pinned_to_node_id(struct toptree *core)
{
	return emu_cores->to_node_id[core->id];
}