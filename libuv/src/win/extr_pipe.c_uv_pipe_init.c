#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_stream_t ;
struct TYPE_6__ {scalar_t__ payload_remaining; } ;
struct TYPE_7__ {int /*<<< orphan*/ * non_overlapped_writes_tail; scalar_t__ ipc_xfer_queue_length; int /*<<< orphan*/  ipc_xfer_queue; TYPE_1__ ipc_data_frame; scalar_t__ ipc_remote_pid; } ;
struct TYPE_8__ {TYPE_2__ conn; } ;
struct TYPE_9__ {int ipc; TYPE_3__ pipe; int /*<<< orphan*/ * name; int /*<<< orphan*/  handle; scalar_t__ reqs_pending; } ;
typedef  TYPE_4__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  QUEUE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UV_NAMED_PIPE ; 
 int /*<<< orphan*/  uv_stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv_pipe_init(uv_loop_t* loop, uv_pipe_t* handle, int ipc) {
  uv_stream_init(loop, (uv_stream_t*)handle, UV_NAMED_PIPE);

  handle->reqs_pending = 0;
  handle->handle = INVALID_HANDLE_VALUE;
  handle->name = NULL;
  handle->pipe.conn.ipc_remote_pid = 0;
  handle->pipe.conn.ipc_data_frame.payload_remaining = 0;
  QUEUE_INIT(&handle->pipe.conn.ipc_xfer_queue);
  handle->pipe.conn.ipc_xfer_queue_length = 0;
  handle->ipc = ipc;
  handle->pipe.conn.non_overlapped_writes_tail = NULL;

  return 0;
}