#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uv_udp_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPV6_MULTICAST_HOPS ; 
 int /*<<< orphan*/  IP_MULTICAST_TTL ; 
 int uv__setsockopt_maybe_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int uv_udp_set_multicast_ttl(uv_udp_t* handle, int ttl) {
/*
 * On Solaris and derivatives such as SmartOS, the length of socket options
 * is sizeof(int) for IPV6_MULTICAST_HOPS and sizeof(char) for
 * IP_MULTICAST_TTL, so hardcode the size of the option in the IPv6 case,
 * and use the general uv__setsockopt_maybe_char call otherwise.
 */
#if defined(__sun) || defined(_AIX) || defined(__OpenBSD__) || \
    defined(__MVS__)
  if (handle->flags & UV_HANDLE_IPV6)
    return uv__setsockopt(handle,
                          IP_MULTICAST_TTL,
                          IPV6_MULTICAST_HOPS,
                          &ttl,
                          sizeof(ttl));
#endif /* defined(__sun) || defined(_AIX) || defined(__OpenBSD__) || \
    defined(__MVS__) */

  return uv__setsockopt_maybe_char(handle,
                                   IP_MULTICAST_TTL,
                                   IPV6_MULTICAST_HOPS,
                                   ttl);
}