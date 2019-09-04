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
struct TYPE_3__ {int /*<<< orphan*/  use; } ;
typedef  TYPE_1__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  target_kill_use ; 

void SP_target_kill( gentity_t *self ) {
	self->use = target_kill_use;
}