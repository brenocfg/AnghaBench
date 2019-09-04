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
struct TYPE_6__ {int backend_fd; void* inotify_watchers; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__inotify_fork (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  uv__platform_loop_delete (TYPE_1__*) ; 
 int uv__platform_loop_init (TYPE_1__*) ; 

int uv__io_fork(uv_loop_t* loop) {
  int err;
  void* old_watchers;

  old_watchers = loop->inotify_watchers;

  uv__close(loop->backend_fd);
  loop->backend_fd = -1;
  uv__platform_loop_delete(loop);

  err = uv__platform_loop_init(loop);
  if (err)
    return err;

  return uv__inotify_fork(loop, old_watchers);
}