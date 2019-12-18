#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* data; } ;
struct TYPE_4__ {TYPE_3__ exit_req; scalar_t__ exit_cb_pending; int /*<<< orphan*/ * child_stdio_buffer; void* process_handle; void* wait_handle; scalar_t__ exit_signal; scalar_t__ pid; int /*<<< orphan*/ * exit_cb; } ;
typedef  TYPE_1__ uv_process_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 void* INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  UV_PROCESS ; 
 int /*<<< orphan*/  UV_PROCESS_EXIT ; 
 int /*<<< orphan*/  UV_REQ_INIT (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uv_process_init(uv_loop_t* loop, uv_process_t* handle) {
  uv__handle_init(loop, (uv_handle_t*) handle, UV_PROCESS);
  handle->exit_cb = NULL;
  handle->pid = 0;
  handle->exit_signal = 0;
  handle->wait_handle = INVALID_HANDLE_VALUE;
  handle->process_handle = INVALID_HANDLE_VALUE;
  handle->child_stdio_buffer = NULL;
  handle->exit_cb_pending = 0;

  UV_REQ_INIT(&handle->exit_req, UV_PROCESS_EXIT);
  handle->exit_req.data = handle;
}