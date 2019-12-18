#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fd; TYPE_3__* stream; } ;
struct TYPE_6__ {int flags; TYPE_1__ data; } ;
typedef  TYPE_2__ uv_stdio_container_t ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  UV_CREATE_PIPE 131 
 int UV_EINVAL ; 
#define  UV_IGNORE 130 
#define  UV_INHERIT_FD 129 
#define  UV_INHERIT_STREAM 128 
 int /*<<< orphan*/  UV_NAMED_PIPE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int uv__make_socketpair (int*,int /*<<< orphan*/ ) ; 
 int uv__stream_fd (TYPE_3__*) ; 

__attribute__((used)) static int uv__process_init_stdio(uv_stdio_container_t* container, int fds[2]) {
  int mask;
  int fd;

  mask = UV_IGNORE | UV_CREATE_PIPE | UV_INHERIT_FD | UV_INHERIT_STREAM;

  switch (container->flags & mask) {
  case UV_IGNORE:
    return 0;

  case UV_CREATE_PIPE:
    assert(container->data.stream != NULL);
    if (container->data.stream->type != UV_NAMED_PIPE)
      return UV_EINVAL;
    else
      return uv__make_socketpair(fds, 0);

  case UV_INHERIT_FD:
  case UV_INHERIT_STREAM:
    if (container->flags & UV_INHERIT_FD)
      fd = container->data.fd;
    else
      fd = uv__stream_fd(container->data.stream);

    if (fd == -1)
      return UV_EINVAL;

    fds[1] = fd;
    return 0;

  default:
    assert(0 && "Unexpected flags");
    return UV_EINVAL;
  }
}