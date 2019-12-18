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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ active_gdns ; 
 int /*<<< orphan*/  free_holder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_storage () ; 
 int /*<<< orphan*/  gdns_free_queue () ; 
 TYPE_1__ gdns_thread ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
house_keeping_holder (void)
{
  /* REVERSE DNS THREAD */
  pthread_mutex_lock (&gdns_thread.mutex);

  /* kill dns pthread */
  active_gdns = 0;
  /* clear holder structure */
  free_holder (&holder);
  /* clear reverse dns queue */
  gdns_free_queue ();
  /* clear the whole storage */
  free_storage ();

  pthread_mutex_unlock (&gdns_thread.mutex);
}