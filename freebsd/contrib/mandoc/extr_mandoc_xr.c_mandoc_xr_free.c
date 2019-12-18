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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mandoc_xr_clear () ; 
 int /*<<< orphan*/ * xr_hash ; 

void
mandoc_xr_free(void)
{
	mandoc_xr_clear();
	free(xr_hash);
	xr_hash = NULL;
}