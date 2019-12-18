#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cma_multicast {TYPE_1__* id_priv; int /*<<< orphan*/  cond; int /*<<< orphan*/  events_completed; } ;
struct TYPE_2__ {int /*<<< orphan*/  mut; int /*<<< orphan*/  cond; int /*<<< orphan*/  events_completed; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucma_complete_mc_event(struct cma_multicast *mc)
{
	pthread_mutex_lock(&mc->id_priv->mut);
	mc->events_completed++;
	pthread_cond_signal(&mc->cond);
	mc->id_priv->events_completed++;
	pthread_cond_signal(&mc->id_priv->cond);
	pthread_mutex_unlock(&mc->id_priv->mut);
}