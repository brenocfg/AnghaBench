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
struct cm_id_private {int /*<<< orphan*/  mut; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cm_id_private*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_cm_free_id(struct cm_id_private *cm_id_priv)
{
	pthread_cond_destroy(&cm_id_priv->cond);
	pthread_mutex_destroy(&cm_id_priv->mut);
	free(cm_id_priv);
}