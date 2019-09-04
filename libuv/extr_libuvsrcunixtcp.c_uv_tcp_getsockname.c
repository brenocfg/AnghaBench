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
struct TYPE_3__ {int delayed_error; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  getsockname ; 
 int uv__getsockpeername (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 

int uv_tcp_getsockname(const uv_tcp_t* handle,
                       struct sockaddr* name,
                       int* namelen) {

  if (handle->delayed_error)
    return handle->delayed_error;

  return uv__getsockpeername((const uv_handle_t*) handle,
                             getsockname,
                             name,
                             namelen);
}