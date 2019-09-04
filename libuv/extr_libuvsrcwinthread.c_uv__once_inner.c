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
struct TYPE_3__ {int ran; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ uv_once_t ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ InterlockedCompareExchangePointer (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ SetEvent (scalar_t__) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv_fatal_error (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void uv__once_inner(uv_once_t* guard, void (*callback)(void)) {
  DWORD result;
  HANDLE existing_event, created_event;

  created_event = CreateEvent(NULL, 1, 0, NULL);
  if (created_event == 0) {
    /* Could fail in a low-memory situation? */
    uv_fatal_error(GetLastError(), "CreateEvent");
  }

  existing_event = InterlockedCompareExchangePointer(&guard->event,
                                                     created_event,
                                                     NULL);

  if (existing_event == NULL) {
    /* We won the race */
    callback();

    result = SetEvent(created_event);
    assert(result);
    guard->ran = 1;

  } else {
    /* We lost the race. Destroy the event we created and wait for the existing
     * one to become signaled. */
    CloseHandle(created_event);
    result = WaitForSingleObject(existing_event, INFINITE);
    assert(result == WAIT_OBJECT_0);
  }
}