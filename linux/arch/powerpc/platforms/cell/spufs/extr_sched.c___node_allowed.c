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
struct spu_context {int /*<<< orphan*/  cpus_allowed; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpumask_intersects (struct cpumask const*,int /*<<< orphan*/ *) ; 
 struct cpumask* cpumask_of_node (int) ; 
 scalar_t__ nr_cpus_node (int) ; 

__attribute__((used)) static int __node_allowed(struct spu_context *ctx, int node)
{
	if (nr_cpus_node(node)) {
		const struct cpumask *mask = cpumask_of_node(node);

		if (cpumask_intersects(mask, &ctx->cpus_allowed))
			return 1;
	}

	return 0;
}