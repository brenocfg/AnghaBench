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

/* Variables and functions */
 int /*<<< orphan*/  ff_mutex ; 
 int /*<<< orphan*/  ff_server_thread ; 
 int ff_stop_server ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

void ff_destroy (void *arg) {
  pthread_mutex_lock (&ff_mutex);
  vkprintf (2, "ff_destroy ()\n");
  ff_stop_server = 1;
  pthread_mutex_unlock (&ff_mutex);
  pthread_join (ff_server_thread, NULL);
  pthread_mutex_destroy (&ff_mutex);
}