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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 scalar_t__ DS_IS_DEFER_DESTROY (int /*<<< orphan*/ *) ; 

uint64_t
dsl_get_defer_destroy(dsl_dataset_t *ds)
{
	return (DS_IS_DEFER_DESTROY(ds) ? 1 : 0);
}