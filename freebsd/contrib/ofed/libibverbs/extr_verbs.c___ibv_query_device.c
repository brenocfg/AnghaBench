#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibv_device_attr {int dummy; } ;
struct TYPE_2__ {int (* query_device ) (struct ibv_context*,struct ibv_device_attr*) ;} ;
struct ibv_context {TYPE_1__ ops; } ;

/* Variables and functions */
 int stub1 (struct ibv_context*,struct ibv_device_attr*) ; 

int __ibv_query_device(struct ibv_context *context,
		       struct ibv_device_attr *device_attr)
{
	return context->ops.query_device(context, device_attr);
}