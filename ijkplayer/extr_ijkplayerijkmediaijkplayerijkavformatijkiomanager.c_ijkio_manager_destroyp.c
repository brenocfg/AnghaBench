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
typedef  int /*<<< orphan*/  IjkIOManagerContext ;

/* Variables and functions */
 int /*<<< orphan*/  ijkio_manager_destroy (int /*<<< orphan*/ *) ; 

void ijkio_manager_destroyp(IjkIOManagerContext **ph)
{
    if (!ph || !*ph)
        return;

    ijkio_manager_destroy(*ph);
    *ph = NULL;
}