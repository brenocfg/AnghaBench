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
struct TYPE_4__ {scalar_t__ sm_object; int /*<<< orphan*/  sm_os; } ;
typedef  TYPE_1__ space_map_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  space_map_free_obj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  space_map_object (TYPE_1__*) ; 

void
space_map_free(space_map_t *sm, dmu_tx_t *tx)
{
	if (sm == NULL)
		return;

	space_map_free_obj(sm->sm_os, space_map_object(sm), tx);
	sm->sm_object = 0;
}