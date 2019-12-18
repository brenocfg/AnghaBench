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
struct cma_id_private {int /*<<< orphan*/  mut; int /*<<< orphan*/  cond; int /*<<< orphan*/  events_completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucma_complete_event(struct cma_id_private *id_priv)
{
	pthread_mutex_lock(&id_priv->mut);
	id_priv->events_completed++;
	pthread_cond_signal(&id_priv->cond);
	pthread_mutex_unlock(&id_priv->mut);
}