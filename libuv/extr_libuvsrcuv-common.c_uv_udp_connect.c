#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int flags; } ;
typedef  TYPE_1__ uv_udp_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int UV_EINVAL ; 
 int UV_EISCONN ; 
 int UV_ENOTCONN ; 
 int UV_HANDLE_UDP_CONNECTED ; 
 scalar_t__ UV_UDP ; 
 int uv__udp_connect (TYPE_1__*,struct sockaddr const*,unsigned int) ; 
 int uv__udp_disconnect (TYPE_1__*) ; 

int uv_udp_connect(uv_udp_t* handle, const struct sockaddr* addr) {
  unsigned int addrlen;

  if (handle->type != UV_UDP)
    return UV_EINVAL;

  /* Disconnect the handle */
  if (addr == NULL) {
    if (!(handle->flags & UV_HANDLE_UDP_CONNECTED))
      return UV_ENOTCONN;

    return uv__udp_disconnect(handle);
  }

  if (addr->sa_family == AF_INET)
    addrlen = sizeof(struct sockaddr_in);
  else if (addr->sa_family == AF_INET6)
    addrlen = sizeof(struct sockaddr_in6);
  else
    return UV_EINVAL;

  if (handle->flags & UV_HANDLE_UDP_CONNECTED)
    return UV_EISCONN;

  return uv__udp_connect(handle, addr, addrlen);
}