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
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int flags; TYPE_1__ io_watcher; } ;
typedef  TYPE_2__ uv_udp_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int UV_HANDLE_IPV6 ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void const*,size_t) ; 

__attribute__((used)) static int uv__setsockopt(uv_udp_t* handle,
                         int option4,
                         int option6,
                         const void* val,
                         size_t size) {
  int r;

  if (handle->flags & UV_HANDLE_IPV6)
    r = setsockopt(handle->io_watcher.fd,
                   IPPROTO_IPV6,
                   option6,
                   val,
                   size);
  else
    r = setsockopt(handle->io_watcher.fd,
                   IPPROTO_IP,
                   option4,
                   val,
                   size);
  if (r)
    return UV__ERR(errno);

  return 0;
}