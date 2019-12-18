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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/ ***** info ; 
 int num_pack ; 

__attribute__((used)) static void free_pack_info(void)
{
	int i;
	for (i = 0; i < num_pack; i++)
		free(info[i]);
	free(info);
}