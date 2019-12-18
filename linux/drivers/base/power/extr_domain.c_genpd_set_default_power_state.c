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
struct generic_pm_domain {int state_count; int /*<<< orphan*/  free_states; struct genpd_power_state* states; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  genpd_free_default_power_state ; 
 struct genpd_power_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genpd_set_default_power_state(struct generic_pm_domain *genpd)
{
	struct genpd_power_state *state;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	genpd->states = state;
	genpd->state_count = 1;
	genpd->free_states = genpd_free_default_power_state;

	return 0;
}