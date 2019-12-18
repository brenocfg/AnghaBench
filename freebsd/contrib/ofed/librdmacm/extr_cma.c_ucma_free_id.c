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
struct TYPE_4__ {struct cma_id_private* path_rec; } ;
struct TYPE_3__ {int /*<<< orphan*/  channel; TYPE_2__ route; } ;
struct cma_id_private {struct cma_id_private* connect; scalar_t__ connect_len; TYPE_1__ id; scalar_t__ sync; int /*<<< orphan*/  mut; int /*<<< orphan*/  cond; scalar_t__ cma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cma_id_private*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_event_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucma_put_device (scalar_t__) ; 
 int /*<<< orphan*/  ucma_remove_id (struct cma_id_private*) ; 

__attribute__((used)) static void ucma_free_id(struct cma_id_private *id_priv)
{
	ucma_remove_id(id_priv);
	if (id_priv->cma_dev)
		ucma_put_device(id_priv->cma_dev);
	pthread_cond_destroy(&id_priv->cond);
	pthread_mutex_destroy(&id_priv->mut);
	if (id_priv->id.route.path_rec)
		free(id_priv->id.route.path_rec);

	if (id_priv->sync)
		rdma_destroy_event_channel(id_priv->id.channel);
	if (id_priv->connect_len)
		free(id_priv->connect);
	free(id_priv);
}