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
struct client_resource {int handle; } ;
struct client {int /*<<< orphan*/  lock; int /*<<< orphan*/  resource_idr; scalar_t__ in_shutdown; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ECANCELED ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  client_get (struct client*) ; 
 int gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct client_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  schedule_if_iso_resource (struct client_resource*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int add_client_resource(struct client *client,
			       struct client_resource *resource, gfp_t gfp_mask)
{
	bool preload = gfpflags_allow_blocking(gfp_mask);
	unsigned long flags;
	int ret;

	if (preload)
		idr_preload(gfp_mask);
	spin_lock_irqsave(&client->lock, flags);

	if (client->in_shutdown)
		ret = -ECANCELED;
	else
		ret = idr_alloc(&client->resource_idr, resource, 0, 0,
				GFP_NOWAIT);
	if (ret >= 0) {
		resource->handle = ret;
		client_get(client);
		schedule_if_iso_resource(resource);
	}

	spin_unlock_irqrestore(&client->lock, flags);
	if (preload)
		idr_preload_end();

	return ret < 0 ? ret : 0;
}