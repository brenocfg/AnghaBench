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
struct TYPE_2__ {int /*<<< orphan*/  fs_counter; } ;

/* Variables and functions */
 TYPE_1__ fortuna_state ; 
 int /*<<< orphan*/  uint128_is_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
random_fortuna_seeded_internal(void)
{
	return (!uint128_is_zero(fortuna_state.fs_counter));
}