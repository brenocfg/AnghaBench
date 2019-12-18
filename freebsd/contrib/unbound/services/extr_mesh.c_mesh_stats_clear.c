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
struct TYPE_2__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct mesh_area {scalar_t__ ans_nodata; int /*<<< orphan*/ * ans_rcode; scalar_t__ ans_bogus; scalar_t__ ans_secure; int /*<<< orphan*/  histogram; scalar_t__ stats_dropped; scalar_t__ stats_jostled; TYPE_1__ replies_sum_wait; scalar_t__ replies_sent; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timehist_clear (int /*<<< orphan*/ ) ; 

void 
mesh_stats_clear(struct mesh_area* mesh)
{
	if(!mesh)
		return;
	mesh->replies_sent = 0;
	mesh->replies_sum_wait.tv_sec = 0;
	mesh->replies_sum_wait.tv_usec = 0;
	mesh->stats_jostled = 0;
	mesh->stats_dropped = 0;
	timehist_clear(mesh->histogram);
	mesh->ans_secure = 0;
	mesh->ans_bogus = 0;
	memset(&mesh->ans_rcode[0], 0, sizeof(size_t)*16);
	mesh->ans_nodata = 0;
}