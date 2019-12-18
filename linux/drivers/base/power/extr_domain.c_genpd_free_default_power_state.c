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
struct genpd_power_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct genpd_power_state*) ; 

__attribute__((used)) static void genpd_free_default_power_state(struct genpd_power_state *states,
					   unsigned int state_count)
{
	kfree(states);
}