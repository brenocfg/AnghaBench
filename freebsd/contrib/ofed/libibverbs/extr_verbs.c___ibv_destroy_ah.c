#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_ah {TYPE_2__* context; } ;
struct TYPE_3__ {int (* destroy_ah ) (struct ibv_ah*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int stub1 (struct ibv_ah*) ; 

int __ibv_destroy_ah(struct ibv_ah *ah)
{
	return ah->context->ops.destroy_ah(ah);
}