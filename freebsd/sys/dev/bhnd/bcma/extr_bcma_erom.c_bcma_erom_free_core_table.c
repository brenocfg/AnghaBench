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
typedef  int /*<<< orphan*/  bhnd_erom_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  free (struct bhnd_core_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcma_erom_free_core_table(bhnd_erom_t *erom, struct bhnd_core_info *cores)
{
	free(cores, M_BHND);
}