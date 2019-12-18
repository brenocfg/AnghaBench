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
struct ibv_cq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  arm_sn; } ;

/* Variables and functions */
 TYPE_1__* to_mcq (struct ibv_cq*) ; 

void mlx5_cq_event(struct ibv_cq *cq)
{
	to_mcq(cq)->arm_sn++;
}