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
struct ibv_context_1_0 {int /*<<< orphan*/  real_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_context_1_0*) ; 
 int ibv_close_device (int /*<<< orphan*/ ) ; 

int __ibv_close_device_1_0(struct ibv_context_1_0 *context)
{
	int ret;

	ret = ibv_close_device(context->real_context);
	if (ret)
		return ret;

	free(context);
	return 0;
}