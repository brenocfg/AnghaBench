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
struct TYPE_7__ {int /*<<< orphan*/  readfile_thread_lock; int /*<<< orphan*/ * readfile_thread_handle; int /*<<< orphan*/ * eof_timer; } ;
struct TYPE_8__ {TYPE_2__ conn; } ;
struct TYPE_6__ {TYPE_4__* data; } ;
struct TYPE_9__ {int flags; TYPE_3__ pipe; TYPE_1__ read_req; } ;
typedef  TYPE_4__ uv_pipe_t ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int UV_HANDLE_NON_OVERLAPPED_PIPE ; 
 int UV_HANDLE_PIPESERVER ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv_connection_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv_pipe_connection_init(uv_pipe_t* handle) {
  uv_connection_init((uv_stream_t*) handle);
  handle->read_req.data = handle;
  handle->pipe.conn.eof_timer = NULL;
  assert(!(handle->flags & UV_HANDLE_PIPESERVER));
  if (handle->flags & UV_HANDLE_NON_OVERLAPPED_PIPE) {
    handle->pipe.conn.readfile_thread_handle = NULL;
    InitializeCriticalSection(&handle->pipe.conn.readfile_thread_lock);
  }
}