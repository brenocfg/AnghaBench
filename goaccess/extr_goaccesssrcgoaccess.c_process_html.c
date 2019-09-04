#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int filenames_idx; char** filenames; scalar_t__ stop_processing; int /*<<< orphan*/  real_time_html; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {int fd; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {scalar_t__ load_from_disk_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 TYPE_5__ conf ; 
 scalar_t__ file_size (char*) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 TYPE_4__ gdns_thread ; 
 TYPE_1__* glog ; 
 TYPE_2__* gwswriter ; 
 int /*<<< orphan*/  holder ; 
 int open_fifoin () ; 
 int /*<<< orphan*/  output_html (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  perform_tail_follow (scalar_t__*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_ready_state () ; 
 int /*<<< orphan*/  usleep (int) ; 
 scalar_t__* xcalloc (int,int) ; 

__attribute__((used)) static void
process_html (const char *filename)
{
  uint64_t *size1 = NULL;
  int i = 0;

  /* render report */
  pthread_mutex_lock (&gdns_thread.mutex);
  output_html (glog, holder, filename);
  pthread_mutex_unlock (&gdns_thread.mutex);
  /* not real time? */
  if (!conf.real_time_html)
    return;
  /* ignore loading from disk */
  if (glog->load_from_disk_only)
    return;

  pthread_mutex_lock (&gwswriter->mutex);
  gwswriter->fd = open_fifoin ();
  pthread_mutex_unlock (&gwswriter->mutex);

  /* open fifo for write */
  if (gwswriter->fd == -1)
    return;

  size1 = xcalloc (conf.filenames_idx, sizeof (uint64_t));
  for (i = 0; i < conf.filenames_idx; ++i) {
    if (conf.filenames[i][0] == '-' && conf.filenames[i][1] == '\0')
      size1[i] = 0;
    else
      size1[i] = file_size (conf.filenames[i]);
  }

  set_ready_state ();
  while (1) {
    if (conf.stop_processing)
      break;

    for (i = 0; i < conf.filenames_idx; ++i)
      perform_tail_follow (&size1[i], conf.filenames[i]);       /* 0.2 secs */
    usleep (800000);    /* 0.8 secs */
  }
  close (gwswriter->fd);
  free (size1);
}