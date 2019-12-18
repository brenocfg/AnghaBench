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
struct bhnd_core_clkctl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_CLKCTL_LOCK_DESTROY (struct bhnd_core_clkctl*) ; 
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  free (struct bhnd_core_clkctl*,int /*<<< orphan*/ ) ; 

void
bhnd_free_core_clkctl(struct bhnd_core_clkctl *clkctl)
{
	BHND_CLKCTL_LOCK_DESTROY(clkctl);

	free(clkctl, M_BHND);
}