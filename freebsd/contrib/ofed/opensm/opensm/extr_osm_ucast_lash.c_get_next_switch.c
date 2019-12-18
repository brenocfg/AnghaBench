#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__** switches; } ;
typedef  TYPE_4__ lash_t ;
struct TYPE_8__ {TYPE_2__* node; } ;
struct TYPE_7__ {TYPE_1__** links; } ;
struct TYPE_6__ {int switch_id; } ;

/* Variables and functions */

__attribute__((used)) static inline int get_next_switch(lash_t *p_lash, int sw, int link)
{
	return p_lash->switches[sw]->node->links[link]->switch_id;
}