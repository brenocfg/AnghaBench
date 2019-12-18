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
typedef  int /*<<< orphan*/  ftree_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  fabric_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fabric_destroy(ftree_fabric_t * p_ftree)
{
	if (!p_ftree)
		return;
	fabric_clear(p_ftree);
	free(p_ftree);
}