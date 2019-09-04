#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_3__ {int fd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  self_pipe; } ;
typedef  TYPE_1__ GWSReader ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fast_forward_client ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ read_fifo (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_self_pipe (int /*<<< orphan*/ ) ; 

void
read_client (void *ptr_data)
{
  GWSReader *reader = (GWSReader *) ptr_data;
  fd_set rfds, wfds;

  FD_ZERO (&rfds);
  FD_ZERO (&wfds);

  /* check we have a fifo for reading */
  if (reader->fd == -1)
    return;

  pthread_mutex_lock (&reader->mutex);
  set_self_pipe (reader->self_pipe);
  pthread_mutex_unlock (&reader->mutex);

  while (1) {
    /* select(2) will block */
    if (read_fifo (reader, rfds, wfds, fast_forward_client))
      break;
  }
  close (reader->fd);
}