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
struct ibv_pd {struct ibv_context* context; } ;
struct TYPE_2__ {struct ibv_pd* (* alloc_pd ) (struct ibv_context*) ;} ;
struct ibv_context {TYPE_1__ ops; } ;

/* Variables and functions */
 struct ibv_pd* stub1 (struct ibv_context*) ; 

struct ibv_pd *__ibv_alloc_pd(struct ibv_context *context)
{
	struct ibv_pd *pd;

	pd = context->ops.alloc_pd(context);
	if (pd)
		pd->context = context;

	return pd;
}