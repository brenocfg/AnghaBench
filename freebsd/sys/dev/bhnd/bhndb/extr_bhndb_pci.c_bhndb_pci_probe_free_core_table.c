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
struct bhnd_core_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  free (struct bhnd_core_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bhndb_pci_probe_free_core_table(struct bhnd_core_info *cores)
{
	free(cores, M_BHND);
}