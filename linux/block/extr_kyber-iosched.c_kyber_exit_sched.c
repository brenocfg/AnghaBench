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
struct kyber_queue_data {int /*<<< orphan*/  cpu_latency; int /*<<< orphan*/ * domain_tokens; int /*<<< orphan*/  timer; } ;
struct elevator_queue {struct kyber_queue_data* elevator_data; } ;

/* Variables and functions */
 int KYBER_NUM_DOMAINS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kyber_queue_data*) ; 
 int /*<<< orphan*/  sbitmap_queue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kyber_exit_sched(struct elevator_queue *e)
{
	struct kyber_queue_data *kqd = e->elevator_data;
	int i;

	del_timer_sync(&kqd->timer);

	for (i = 0; i < KYBER_NUM_DOMAINS; i++)
		sbitmap_queue_free(&kqd->domain_tokens[i]);
	free_percpu(kqd->cpu_latency);
	kfree(kqd);
}