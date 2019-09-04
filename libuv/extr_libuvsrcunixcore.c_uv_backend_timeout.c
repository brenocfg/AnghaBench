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
struct TYPE_6__ {scalar_t__ stop_flag; scalar_t__ closing_handles; int /*<<< orphan*/  pending_queue; int /*<<< orphan*/  idle_handles; } ;
typedef  TYPE_1__ uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__has_active_handles (TYPE_1__ const*) ; 
 int /*<<< orphan*/  uv__has_active_reqs (TYPE_1__ const*) ; 
 int uv__next_timeout (TYPE_1__ const*) ; 

int uv_backend_timeout(const uv_loop_t* loop) {
  if (loop->stop_flag != 0)
    return 0;

  if (!uv__has_active_handles(loop) && !uv__has_active_reqs(loop))
    return 0;

  if (!QUEUE_EMPTY(&loop->idle_handles))
    return 0;

  if (!QUEUE_EMPTY(&loop->pending_queue))
    return 0;

  if (loop->closing_handles)
    return 0;

  return uv__next_timeout(loop);
}