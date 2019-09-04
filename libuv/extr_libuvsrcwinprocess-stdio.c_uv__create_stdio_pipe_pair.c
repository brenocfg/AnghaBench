#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ handle; int /*<<< orphan*/  flags; scalar_t__ ipc; } ;
typedef  TYPE_1__ uv_pipe_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  pipe_name ;
struct TYPE_8__ {int nLength; scalar_t__ bInheritHandle; int /*<<< orphan*/ * lpSecurityDescriptor; } ;
typedef  TYPE_2__ SECURITY_ATTRIBUTES ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConnectNamedPipe (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileA (char*,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ERROR_PIPE_CONNECTED ; 
 int /*<<< orphan*/  FILE_FLAG_OVERLAPPED ; 
 int FILE_READ_ATTRIBUTES ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetLastError () ; 
 scalar_t__ GetNamedPipeHandleState (scalar_t__,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int PIPE_ACCESS_INBOUND ; 
 int PIPE_ACCESS_OUTBOUND ; 
 int PIPE_READMODE_BYTE ; 
 int PIPE_WAIT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UV_HANDLE_READABLE ; 
 int /*<<< orphan*/  UV_HANDLE_WRITABLE ; 
 unsigned int UV_OVERLAPPED_PIPE ; 
 unsigned int UV_READABLE_PIPE ; 
 unsigned int UV_WRITABLE_PIPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv_pipe_cleanup (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int uv_stdio_pipe_server (int /*<<< orphan*/ *,TYPE_1__*,int,char*,int) ; 

__attribute__((used)) static int uv__create_stdio_pipe_pair(uv_loop_t* loop,
    uv_pipe_t* server_pipe, HANDLE* child_pipe_ptr, unsigned int flags) {
  char pipe_name[64];
  SECURITY_ATTRIBUTES sa;
  DWORD server_access = 0;
  DWORD client_access = 0;
  HANDLE child_pipe = INVALID_HANDLE_VALUE;
  int err;
  int overlap;

  if (flags & UV_READABLE_PIPE) {
    /* The server needs inbound access too, otherwise CreateNamedPipe() won't
     * give us the FILE_READ_ATTRIBUTES permission. We need that to probe the
     * state of the write buffer when we're trying to shutdown the pipe. */
    server_access |= PIPE_ACCESS_OUTBOUND | PIPE_ACCESS_INBOUND;
    client_access |= GENERIC_READ | FILE_WRITE_ATTRIBUTES;
  }
  if (flags & UV_WRITABLE_PIPE) {
    server_access |= PIPE_ACCESS_INBOUND;
    client_access |= GENERIC_WRITE | FILE_READ_ATTRIBUTES;
  }

  /* Create server pipe handle. */
  err = uv_stdio_pipe_server(loop,
                             server_pipe,
                             server_access,
                             pipe_name,
                             sizeof(pipe_name));
  if (err)
    goto error;

  /* Create child pipe handle. */
  sa.nLength = sizeof sa;
  sa.lpSecurityDescriptor = NULL;
  sa.bInheritHandle = TRUE;

  overlap = server_pipe->ipc || (flags & UV_OVERLAPPED_PIPE);
  child_pipe = CreateFileA(pipe_name,
                           client_access,
                           0,
                           &sa,
                           OPEN_EXISTING,
                           overlap ? FILE_FLAG_OVERLAPPED : 0,
                           NULL);
  if (child_pipe == INVALID_HANDLE_VALUE) {
    err = GetLastError();
    goto error;
  }

#ifndef NDEBUG
  /* Validate that the pipe was opened in the right mode. */
  {
    DWORD mode;
    BOOL r = GetNamedPipeHandleState(child_pipe,
                                     &mode,
                                     NULL,
                                     NULL,
                                     NULL,
                                     NULL,
                                     0);
    assert(r == TRUE);
    assert(mode == (PIPE_READMODE_BYTE | PIPE_WAIT));
  }
#endif

  /* Do a blocking ConnectNamedPipe. This should not block because we have both
   * ends of the pipe created. */
  if (!ConnectNamedPipe(server_pipe->handle, NULL)) {
    if (GetLastError() != ERROR_PIPE_CONNECTED) {
      err = GetLastError();
      goto error;
    }
  }

  /* The server end is now readable and/or writable. */
  if (flags & UV_READABLE_PIPE)
    server_pipe->flags |= UV_HANDLE_WRITABLE;
  if (flags & UV_WRITABLE_PIPE)
    server_pipe->flags |= UV_HANDLE_READABLE;

  *child_pipe_ptr = child_pipe;
  return 0;

 error:
  if (server_pipe->handle != INVALID_HANDLE_VALUE) {
    uv_pipe_cleanup(loop, server_pipe);
  }

  if (child_pipe != INVALID_HANDLE_VALUE) {
    CloseHandle(child_pipe);
  }

  return err;
}