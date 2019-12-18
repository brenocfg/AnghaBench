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
typedef  size_t u8 ;
struct ib_sa_mcmember_rec {int /*<<< orphan*/  mgid; } ;
struct ib_sa_multicast {int (* callback ) (int,struct ib_sa_multicast*) ;void* context; int /*<<< orphan*/  comp_mask; struct ib_sa_mcmember_rec rec; } ;
struct mcast_member {struct ib_sa_multicast multicast; int /*<<< orphan*/  group; int /*<<< orphan*/  state; int /*<<< orphan*/  refcount; int /*<<< orphan*/  comp; struct ib_sa_client* client; } ;
struct mcast_device {size_t start_port; int /*<<< orphan*/ * port; } ;
struct ib_sa_client {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  ib_sa_comp_mask ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct ib_sa_multicast* ERR_PTR (int) ; 
 int /*<<< orphan*/  MCAST_JOINING ; 
 int /*<<< orphan*/  acquire_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct mcast_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_sa_client_get (struct ib_sa_client*) ; 
 int /*<<< orphan*/  ib_sa_client_put (struct ib_sa_client*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_member*) ; 
 struct mcast_member* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcast_client ; 
 int /*<<< orphan*/  queue_join (struct mcast_member*) ; 

struct ib_sa_multicast *
ib_sa_join_multicast(struct ib_sa_client *client,
		     struct ib_device *device, u8 port_num,
		     struct ib_sa_mcmember_rec *rec,
		     ib_sa_comp_mask comp_mask, gfp_t gfp_mask,
		     int (*callback)(int status,
				     struct ib_sa_multicast *multicast),
		     void *context)
{
	struct mcast_device *dev;
	struct mcast_member *member;
	struct ib_sa_multicast *multicast;
	int ret;

	dev = ib_get_client_data(device, &mcast_client);
	if (!dev)
		return ERR_PTR(-ENODEV);

	member = kmalloc(sizeof *member, gfp_mask);
	if (!member)
		return ERR_PTR(-ENOMEM);

	ib_sa_client_get(client);
	member->client = client;
	member->multicast.rec = *rec;
	member->multicast.comp_mask = comp_mask;
	member->multicast.callback = callback;
	member->multicast.context = context;
	init_completion(&member->comp);
	atomic_set(&member->refcount, 1);
	member->state = MCAST_JOINING;

	member->group = acquire_group(&dev->port[port_num - dev->start_port],
				      &rec->mgid, gfp_mask);
	if (!member->group) {
		ret = -ENOMEM;
		goto err;
	}

	/*
	 * The user will get the multicast structure in their callback.  They
	 * could then free the multicast structure before we can return from
	 * this routine.  So we save the pointer to return before queuing
	 * any callback.
	 */
	multicast = &member->multicast;
	queue_join(member);
	return multicast;

err:
	ib_sa_client_put(client);
	kfree(member);
	return ERR_PTR(ret);
}