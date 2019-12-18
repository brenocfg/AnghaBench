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
struct pmcpl_ct_sample {int /*<<< orphan*/ * sb; scalar_t__ npmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmcpl_ct_samples_free(struct pmcpl_ct_sample *samples)
{

	samples->npmcs = 0;
	free(samples->sb);
	samples->sb = NULL;
}