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
struct spu_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runq_lock; } ;

/* Variables and functions */
 int __node_allowed (struct spu_context*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* spu_prio ; 

__attribute__((used)) static int node_allowed(struct spu_context *ctx, int node)
{
	int rval;

	spin_lock(&spu_prio->runq_lock);
	rval = __node_allowed(ctx, node);
	spin_unlock(&spu_prio->runq_lock);

	return rval;
}