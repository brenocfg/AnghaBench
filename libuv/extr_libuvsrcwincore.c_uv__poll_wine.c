#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_req_t ;
struct TYPE_5__ {scalar_t__ time; int /*<<< orphan*/  iocp; } ;
typedef  TYPE_1__ uv_loop_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  int /*<<< orphan*/  OVERLAPPED ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetQueuedCompletionStatus (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 int /*<<< orphan*/  uv_fatal_error (scalar_t__,char*) ; 
 int /*<<< orphan*/  uv_insert_pending_req (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uv_overlapped_to_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_update_time (TYPE_1__*) ; 

__attribute__((used)) static void uv__poll_wine(uv_loop_t* loop, DWORD timeout) {
  DWORD bytes;
  ULONG_PTR key;
  OVERLAPPED* overlapped;
  uv_req_t* req;
  int repeat;
  uint64_t timeout_time;

  timeout_time = loop->time + timeout;

  for (repeat = 0; ; repeat++) {
    GetQueuedCompletionStatus(loop->iocp,
                              &bytes,
                              &key,
                              &overlapped,
                              timeout);

    if (overlapped) {
      /* Package was dequeued */
      req = uv_overlapped_to_req(overlapped);
      uv_insert_pending_req(loop, req);

      /* Some time might have passed waiting for I/O,
       * so update the loop time here.
       */
      uv_update_time(loop);
    } else if (GetLastError() != WAIT_TIMEOUT) {
      /* Serious error */
      uv_fatal_error(GetLastError(), "GetQueuedCompletionStatus");
    } else if (timeout > 0) {
      /* GetQueuedCompletionStatus can occasionally return a little early.
       * Make sure that the desired timeout target time is reached.
       */
      uv_update_time(loop);
      if (timeout_time > loop->time) {
        timeout = (DWORD)(timeout_time - loop->time);
        /* The first call to GetQueuedCompletionStatus should return very
         * close to the target time and the second should reach it, but
         * this is not stated in the documentation. To make sure a busy
         * loop cannot happen, the timeout is increased exponentially
         * starting on the third round.
         */
        timeout += repeat ? (1 << (repeat - 1)) : 0;
        continue;
      }
    }
    break;
  }
}