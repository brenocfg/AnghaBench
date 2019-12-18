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
struct TYPE_2__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  not_empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdns_queue ; 
 TYPE_1__ gdns_thread ; 
 int /*<<< orphan*/  gqueue_enqueue (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gqueue_find (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gqueue_full (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
dns_resolver (char *addr)
{
  pthread_mutex_lock (&gdns_thread.mutex);
  /* queue is not full and the IP address is not in the queue */
  if (!gqueue_full (gdns_queue) && !gqueue_find (gdns_queue, addr)) {
    /* add the IP to the queue */
    gqueue_enqueue (gdns_queue, addr);
    pthread_cond_broadcast (&gdns_thread.not_empty);
  }
  pthread_mutex_unlock (&gdns_thread.mutex);
}