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
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int uv__duplicate_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__get_osfhandle (int) ; 

__attribute__((used)) static int uv__duplicate_fd(uv_loop_t* loop, int fd, HANDLE* dup) {
  HANDLE handle;

  if (fd == -1) {
    *dup = INVALID_HANDLE_VALUE;
    return ERROR_INVALID_HANDLE;
  }

  handle = uv__get_osfhandle(fd);
  return uv__duplicate_handle(loop, handle, dup);
}