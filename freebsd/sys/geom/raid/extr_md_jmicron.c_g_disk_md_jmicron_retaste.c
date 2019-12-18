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
 int /*<<< orphan*/  G_RAID_DEBUG (int,char*) ; 
 int /*<<< orphan*/  M_MD_JMICRON ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_class ; 
 int /*<<< orphan*/  g_retaste (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_disk_md_jmicron_retaste(void *arg, int pending)
{

	G_RAID_DEBUG(1, "Array is not complete, trying to retaste.");
	g_retaste(&g_raid_class);
	free(arg, M_MD_JMICRON);
}