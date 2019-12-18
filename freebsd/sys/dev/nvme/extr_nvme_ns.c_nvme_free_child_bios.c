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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NVME ; 
 int /*<<< orphan*/  free (struct bio**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 

__attribute__((used)) static void
nvme_free_child_bios(int num_bios, struct bio **child_bios)
{
	int i;

	for (i = 0; i < num_bios; i++) {
		if (child_bios[i] != NULL)
			g_destroy_bio(child_bios[i]);
	}

	free(child_bios, M_NVME);
}