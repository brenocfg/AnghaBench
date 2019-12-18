#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_req_t ;
struct TYPE_8__ {scalar_t__ time; int /*<<< orphan*/  iocp; } ;
typedef  TYPE_1__ uv_loop_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t ULONG ;
struct TYPE_9__ {scalar_t__ lpOverlapped; } ;
typedef  TYPE_2__ OVERLAPPED_ENTRY ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetQueuedCompletionStatusEx (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,size_t*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 int /*<<< orphan*/  uv_fatal_error (scalar_t__,char*) ; 
 int /*<<< orphan*/  uv_insert_pending_req (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uv_overlapped_to_req (scalar_t__) ; 
 int /*<<< orphan*/  uv_update_time (TYPE_1__*) ; 

__attribute__((used)) static void uv__poll(uv_loop_t* loop, DWORD timeout) {
  BOOL success;
  uv_req_t* req;
  OVERLAPPED_ENTRY overlappeds[128];
  ULONG count;
  ULONG i;
  int repeat;
  uint64_t timeout_time;

  timeout_time = loop->time + timeout;

  for (repeat = 0; ; repeat++) {
    success = GetQueuedCompletionStatusEx(loop->iocp,
                                          overlappeds,
                                          ARRAY_SIZE(overlappeds),
                                          &count,
                                          timeout,
                                          FALSE);

    if (success) {
      for (i = 0; i < count; i++) {
        /* Package was dequeued, but see if it is not a empty package
         * meant only to wake us up.
         */
        if (overlappeds[i].lpOverlapped) {
          req = uv_overlapped_to_req(overlappeds[i].lpOverlapped);
          uv_insert_pending_req(loop, req);
        }
      }

      /* Some time might have passed waiting for I/O,
       * so update the loop time here.
       */
      uv_update_time(loop);
    } else if (GetLastError() != WAIT_TIMEOUT) {
      /* Serious error */
      uv_fatal_error(GetLastError(), "GetQueuedCompletionStatusEx");
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