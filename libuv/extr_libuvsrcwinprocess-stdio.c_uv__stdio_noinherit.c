#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int CHILD_STDIO_COUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ CHILD_STDIO_HANDLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HANDLE_FLAG_INHERIT ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetHandleInformation (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uv__stdio_noinherit(BYTE* buffer) {
  int i, count;

  count = CHILD_STDIO_COUNT(buffer);
  for (i = 0; i < count; i++) {
    HANDLE handle = CHILD_STDIO_HANDLE(buffer, i);
    if (handle != INVALID_HANDLE_VALUE) {
      SetHandleInformation(handle, HANDLE_FLAG_INHERIT, 0);
    }
  }
}