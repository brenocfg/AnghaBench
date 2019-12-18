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
struct ibv_comp_channel {int dummy; } ;
struct ibv_abi_compat_v2 {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibv_destroy_comp_channel_v2(struct ibv_comp_channel *channel)
{
	struct ibv_abi_compat_v2 *t = (struct ibv_abi_compat_v2 *) channel;
	pthread_mutex_unlock(&t->in_use);
	return 0;
}