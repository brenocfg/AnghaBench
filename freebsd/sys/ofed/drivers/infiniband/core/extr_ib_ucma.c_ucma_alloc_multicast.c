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
struct ucma_multicast {scalar_t__ id; int /*<<< orphan*/  list; struct ucma_context* ctx; } ;
struct ucma_context {int /*<<< orphan*/  mc_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ idr_alloc (int /*<<< orphan*/ *,struct ucma_multicast*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ucma_multicast*) ; 
 struct ucma_multicast* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multicast_idr ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ucma_multicast* ucma_alloc_multicast(struct ucma_context *ctx)
{
	struct ucma_multicast *mc;

	mc = kzalloc(sizeof(*mc), GFP_KERNEL);
	if (!mc)
		return NULL;

	mutex_lock(&mut);
	mc->id = idr_alloc(&multicast_idr, mc, 0, 0, GFP_KERNEL);
	mutex_unlock(&mut);
	if (mc->id < 0)
		goto error;

	mc->ctx = ctx;
	list_add_tail(&mc->list, &ctx->mc_list);
	return mc;

error:
	kfree(mc);
	return NULL;
}