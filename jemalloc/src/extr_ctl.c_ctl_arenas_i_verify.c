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
struct TYPE_4__ {TYPE_1__** arenas; } ;
struct TYPE_3__ {int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 size_t UINT_MAX ; 
 size_t arenas_i2a_impl (size_t,int,int) ; 
 TYPE_2__* ctl_arenas ; 

__attribute__((used)) static bool
ctl_arenas_i_verify(size_t i) {
	size_t a = arenas_i2a_impl(i, true, true);
	if (a == UINT_MAX || !ctl_arenas->arenas[a]->initialized) {
		return true;
	}

	return false;
}