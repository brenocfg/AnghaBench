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
struct TYPE_8__ {TYPE_1__* item; scalar_t__ count; } ;
typedef  TYPE_2__ gentity_t ;
struct TYPE_7__ {scalar_t__ quantity; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddScore (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  dmlab_set_map_finished (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

int Pickup_Goal( gentity_t *ent, gentity_t *other ) {
	AddScore( other, NULL, ent->count ? ent->count : ent->item->quantity, "PICKUP_GOAL", ent );
	dmlab_set_map_finished( qtrue );
	return -1;
}