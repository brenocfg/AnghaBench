#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
struct TYPE_5__ {int flags; TYPE_1__ data; } ;
typedef  TYPE_2__ uv_stdio_container_t ;

/* Variables and functions */
 int UV_CREATE_PIPE ; 
 int UV_HANDLE_READABLE ; 
 int UV_HANDLE_WRITABLE ; 
 int UV_READABLE_PIPE ; 
 int UV_WRITABLE_PIPE ; 
 int /*<<< orphan*/  abort () ; 
 int uv__close (int) ; 
 int /*<<< orphan*/  uv__nonblock (int,int) ; 
 int uv__stream_open (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int uv__process_open_stream(uv_stdio_container_t* container,
                                   int pipefds[2]) {
  int flags;
  int err;

  if (!(container->flags & UV_CREATE_PIPE) || pipefds[0] < 0)
    return 0;

  err = uv__close(pipefds[1]);
  if (err != 0)
    abort();

  pipefds[1] = -1;
  uv__nonblock(pipefds[0], 1);

  flags = 0;
  if (container->flags & UV_WRITABLE_PIPE)
    flags |= UV_HANDLE_READABLE;
  if (container->flags & UV_READABLE_PIPE)
    flags |= UV_HANDLE_WRITABLE;

  return uv__stream_open(container->data.stream, pipefds[0], flags);
}