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
struct TYPE_4__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__ gdns_thread ; 
 char* get_json (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glog ; 
 TYPE_1__* gwswriter ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_holder_to_client (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
fast_forward_client (int listener)
{
  char *json = NULL;

  pthread_mutex_lock (&gdns_thread.mutex);
  json = get_json (glog, holder, 0);
  pthread_mutex_unlock (&gdns_thread.mutex);

  if (json == NULL)
    return;

  pthread_mutex_lock (&gwswriter->mutex);
  send_holder_to_client (gwswriter->fd, listener, json, strlen (json));
  pthread_mutex_unlock (&gwswriter->mutex);
  free (json);
}