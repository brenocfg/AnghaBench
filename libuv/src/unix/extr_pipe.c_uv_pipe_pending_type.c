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
struct TYPE_3__ {int accepted_fd; int /*<<< orphan*/  ipc; } ;
typedef  TYPE_1__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_handle_type ;

/* Variables and functions */
 int /*<<< orphan*/  UV_UNKNOWN_HANDLE ; 
 int /*<<< orphan*/  uv__handle_type (int) ; 

uv_handle_type uv_pipe_pending_type(uv_pipe_t* handle) {
  if (!handle->ipc)
    return UV_UNKNOWN_HANDLE;

  if (handle->accepted_fd == -1)
    return UV_UNKNOWN_HANDLE;
  else
    return uv__handle_type(handle->accepted_fd);
}