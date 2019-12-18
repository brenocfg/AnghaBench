#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_6__ {int /*<<< orphan*/  thread; int /*<<< orphan*/ * server; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ GWSWriter ;
typedef  TYPE_1__ GWSReader ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,TYPE_1__*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_client ; 
 int /*<<< orphan*/  set_ws_opts ; 
 int /*<<< orphan*/  start_server ; 
 int /*<<< orphan*/ * ws_init (char*,char*,int /*<<< orphan*/ ) ; 

int
setup_ws_server (GWSWriter * gwswriter, GWSReader * gwsreader)
{
  int id;
  pthread_t *thread;

  if (pthread_mutex_init (&gwswriter->mutex, NULL))
    FATAL ("Failed init gwswriter mutex");
  if (pthread_mutex_init (&gwsreader->mutex, NULL))
    FATAL ("Failed init gwsreader mutex");

  /* send WS data thread */
  thread = &gwswriter->thread;

  /* pre-init the websocket server, to ensure the FIFOs are created */
  if ((gwswriter->server = ws_init ("0.0.0.0", "7890", set_ws_opts)) == NULL)
    FATAL ("Failed init websocket");

  id = pthread_create (&(*thread), NULL, (void *) &start_server, gwswriter);
  if (id)
    FATAL ("Return code from pthread_create(): %d", id);

  /* read WS data thread */
  thread = &gwsreader->thread;
  id = pthread_create (&(*thread), NULL, (void *) &read_client, gwsreader);
  if (id)
    FATAL ("Return code from pthread_create(): %d", id);

  return 0;
}