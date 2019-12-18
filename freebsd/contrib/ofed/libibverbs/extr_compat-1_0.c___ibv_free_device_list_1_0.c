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
typedef  int /*<<< orphan*/ **** ibv_device_1_0 ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ******) ; 
 int /*<<< orphan*/  ibv_free_device_list (void*) ; 

void __ibv_free_device_list_1_0(struct ibv_device_1_0 **list)
{
	struct ibv_device_1_0 **l = list;

	while (*l) {
		free(*l);
		++l;
	}

	ibv_free_device_list((void *) list[-1]);
	free(list - 1);
}