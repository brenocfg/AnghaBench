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
struct rdma_event_channel {int dummy; } ;
struct rdma_cm_id {int dummy; } ;
struct TYPE_4__ {struct rdma_event_channel* channel; TYPE_1__* nodes; } ;
struct TYPE_3__ {struct rdma_cm_id* cma_id; } ;

/* Variables and functions */
 int connections ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 struct rdma_event_channel* rdma_create_event_channel () ; 
 int /*<<< orphan*/  rdma_destroy_event_channel (struct rdma_event_channel*) ; 
 int rdma_migrate_id (struct rdma_cm_id*,struct rdma_event_channel*) ; 
 TYPE_2__ test ; 

__attribute__((used)) static int migrate_channel(struct rdma_cm_id *listen_id)
{
	struct rdma_event_channel *channel;
	int i, ret;

	printf("migrating to new event channel\n");

	channel = rdma_create_event_channel();
	if (!channel) {
		perror("cmatose: failed to create event channel");
		return -1;
	}

	ret = 0;
	if (listen_id)
		ret = rdma_migrate_id(listen_id, channel);

	for (i = 0; i < connections && !ret; i++)
		ret = rdma_migrate_id(test.nodes[i].cma_id, channel);

	if (!ret) {
		rdma_destroy_event_channel(test.channel);
		test.channel = channel;
	} else
		perror("cmatose: failure migrating to channel");

	return ret;
}