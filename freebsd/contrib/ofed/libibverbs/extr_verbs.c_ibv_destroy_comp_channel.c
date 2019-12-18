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
struct ibv_context {int /*<<< orphan*/  mutex; } ;
struct ibv_comp_channel {int /*<<< orphan*/  fd; scalar_t__ refcnt; struct ibv_context* context; } ;

/* Variables and functions */
 int EBUSY ; 
 int abi_ver ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ibv_comp_channel*) ; 
 int ibv_destroy_comp_channel_v2 (struct ibv_comp_channel*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int ibv_destroy_comp_channel(struct ibv_comp_channel *channel)
{
	struct ibv_context *context;
	int ret;

	context = channel->context;
	pthread_mutex_lock(&context->mutex);

	if (channel->refcnt) {
		ret = EBUSY;
		goto out;
	}

	if (abi_ver <= 2) {
		ret = ibv_destroy_comp_channel_v2(channel);
		goto out;
	}

	close(channel->fd);
	free(channel);
	ret = 0;

out:
	pthread_mutex_unlock(&context->mutex);

	return ret;
}