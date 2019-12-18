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
struct rdma_event_channel {scalar_t__ fd; } ;

/* Variables and functions */
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  free (struct rdma_event_channel*) ; 
 struct rdma_event_channel* malloc (int) ; 
 scalar_t__ open (char*,int) ; 
 scalar_t__ ucma_init () ; 

struct rdma_event_channel *rdma_create_event_channel(void)
{
	struct rdma_event_channel *channel;

	if (ucma_init())
		return NULL;

	channel = malloc(sizeof(*channel));
	if (!channel)
		return NULL;

	channel->fd = open("/dev/rdma_cm", O_RDWR | O_CLOEXEC);
	if (channel->fd < 0) {
		goto err;
	}
	return channel;
err:
	free(channel);
	return NULL;
}