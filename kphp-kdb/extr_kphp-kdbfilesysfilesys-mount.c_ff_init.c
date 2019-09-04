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
struct fuse_conn_info {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 int /*<<< orphan*/  ff_mutex ; 
 int /*<<< orphan*/  ff_server_thread ; 
 scalar_t__ ff_start_server ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_attr_setstacksize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_server ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

void *ff_init (struct fuse_conn_info *conn) {
  vkprintf (2, "ff_init\n");
  pthread_mutex_init (&ff_mutex, NULL);
  if (ff_start_server) {
    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setstacksize (&attr, 4 << 20);
    pthread_create (&ff_server_thread, &attr, start_server, NULL);
    pthread_attr_destroy (&attr);
    ff_start_server = 0;
  }
  return NULL;
}