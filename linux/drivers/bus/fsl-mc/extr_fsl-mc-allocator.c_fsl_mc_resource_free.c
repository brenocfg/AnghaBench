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
struct fsl_mc_resource_pool {scalar_t__ type; scalar_t__ free_count; scalar_t__ max_count; int /*<<< orphan*/  mutex; int /*<<< orphan*/  free_list; } ;
struct fsl_mc_resource {scalar_t__ type; int /*<<< orphan*/  node; struct fsl_mc_resource_pool* parent_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fsl_mc_resource_free(struct fsl_mc_resource *resource)
{
	struct fsl_mc_resource_pool *res_pool;

	res_pool = resource->parent_pool;
	if (resource->type != res_pool->type)
		return;

	mutex_lock(&res_pool->mutex);
	if (res_pool->free_count < 0 ||
	    res_pool->free_count >= res_pool->max_count)
		goto out_unlock;

	if (!list_empty(&resource->node))
		goto out_unlock;

	list_add_tail(&resource->node, &res_pool->free_list);
	res_pool->free_count++;
out_unlock:
	mutex_unlock(&res_pool->mutex);
}