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
 int /*<<< orphan*/  bridge_ifs ; 
 int /*<<< orphan*/  bridge_ifs_free (int /*<<< orphan*/ *) ; 

void
bridge_ifs_fini(void)
{
	bridge_ifs_free(&bridge_ifs);
}