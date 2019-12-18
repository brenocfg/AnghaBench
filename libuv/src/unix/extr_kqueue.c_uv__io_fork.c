#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int backend_fd; int /*<<< orphan*/ * cf_state; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int uv__has_forked_with_cfrunloop ; 
 int uv__kqueue_init (TYPE_1__*) ; 

int uv__io_fork(uv_loop_t* loop) {
  int err;
  loop->backend_fd = -1;
  err = uv__kqueue_init(loop);
  if (err)
    return err;

#if defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1070
  if (loop->cf_state != NULL) {
    /* We cannot start another CFRunloop and/or thread in the child
       process; CF aborts if you try or if you try to touch the thread
       at all to kill it. So the best we can do is ignore it from now
       on. This means we can't watch directories in the same way
       anymore (like other BSDs). It also means we cannot properly
       clean up the allocated resources; calling
       uv__fsevents_loop_delete from uv_loop_close will crash the
       process. So we sidestep the issue by pretending like we never
       started it in the first place.
    */
    uv__has_forked_with_cfrunloop = 1;
    uv__free(loop->cf_state);
    loop->cf_state = NULL;
  }
#endif /* #if defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1070 */
  return err;
}