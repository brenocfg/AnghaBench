#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_7__ {int /*<<< orphan*/ * self_pipe; } ;
typedef  TYPE_1__ WSServer ;
struct TYPE_9__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * self_pipe; } ;
struct TYPE_8__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  mutex; TYPE_1__* server; } ;
typedef  TYPE_2__ GWSWriter ;
typedef  TYPE_3__ GWSReader ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ errno ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ws_stop (TYPE_1__*) ; 

void
stop_ws_server (GWSWriter * gwswriter, GWSReader * gwsreader)
{
  pthread_t writer, reader;
  WSServer *server = NULL;

  if (!gwsreader || !gwswriter)
    return;
  if (!(server = gwswriter->server))
    return;

  pthread_mutex_lock (&gwsreader->mutex);
  if ((write (gwsreader->self_pipe[1], "x", 1)) == -1 && errno != EAGAIN)
    LOG (("Unable to write to self pipe on pipeout.\n"));
  pthread_mutex_unlock (&gwsreader->mutex);

  pthread_mutex_lock (&gwswriter->mutex);
  /* if it fails to write, force stop */
  if ((write (server->self_pipe[1], "x", 1)) == -1 && errno != EAGAIN)
    ws_stop (server);
  pthread_mutex_unlock (&gwswriter->mutex);

  reader = gwsreader->thread;
  if (pthread_join (reader, NULL) != 0)
    LOG (("Unable to join thread: %d %s\n", reader, strerror (errno)));

  writer = gwswriter->thread;
  if (pthread_join (writer, NULL) != 0)
    LOG (("Unable to join thread: %d %s\n", writer, strerror (errno)));
}