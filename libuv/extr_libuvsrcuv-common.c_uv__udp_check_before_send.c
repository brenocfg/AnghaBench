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
struct TYPE_3__ {scalar_t__ type; int flags; } ;
typedef  TYPE_1__ uv_udp_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int UV_EDESTADDRREQ ; 
 int UV_EINVAL ; 
 int UV_EISCONN ; 
 int UV_HANDLE_UDP_CONNECTED ; 
 scalar_t__ UV_UDP ; 

int uv__udp_check_before_send(uv_udp_t* handle, const struct sockaddr* addr) {
  unsigned int addrlen;

  if (handle->type != UV_UDP)
    return UV_EINVAL;

  if (addr != NULL && (handle->flags & UV_HANDLE_UDP_CONNECTED))
    return UV_EISCONN;

  if (addr == NULL && !(handle->flags & UV_HANDLE_UDP_CONNECTED))
    return UV_EDESTADDRREQ;

  if (addr != NULL) {
    if (addr->sa_family == AF_INET)
      addrlen = sizeof(struct sockaddr_in);
    else if (addr->sa_family == AF_INET6)
      addrlen = sizeof(struct sockaddr_in6);
#if defined(AF_UNIX) && !defined(_WIN32)
    else if (addr->sa_family == AF_UNIX)
      addrlen = sizeof(struct sockaddr_un);
#endif
    else
      return UV_EINVAL;
  } else {
    addrlen = 0;
  }

  return addrlen;
}