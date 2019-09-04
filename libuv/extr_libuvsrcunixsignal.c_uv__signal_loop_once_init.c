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
struct TYPE_4__ {int* signal_pipefd; int /*<<< orphan*/  signal_io_watcher; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  UV__F_NONBLOCK ; 
 int /*<<< orphan*/  uv__io_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uv__io_start (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv__make_pipe (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__signal_event ; 

__attribute__((used)) static int uv__signal_loop_once_init(uv_loop_t* loop) {
  int err;

  /* Return if already initialized. */
  if (loop->signal_pipefd[0] != -1)
    return 0;

  err = uv__make_pipe(loop->signal_pipefd, UV__F_NONBLOCK);
  if (err)
    return err;

  uv__io_init(&loop->signal_io_watcher,
              uv__signal_event,
              loop->signal_pipefd[0]);
  uv__io_start(loop, &loop->signal_io_watcher, POLLIN);

  return 0;
}