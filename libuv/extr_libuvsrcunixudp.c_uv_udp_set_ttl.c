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
 int /*<<< orphan*/  IPV6_UNICAST_HOPS ; 
 int /*<<< orphan*/  IP_TTL ; 
 int UV_EINVAL ; 
 int uv__setsockopt_maybe_char (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int uv_udp_set_ttl(uv_udp_t* handle, int ttl) {
  if (ttl < 1 || ttl > 255)
    return UV_EINVAL;

#if defined(__MVS__)
  if (!(handle->flags & UV_HANDLE_IPV6))
    return UV_ENOTSUP;  /* zOS does not support setting ttl for IPv4 */
#endif

/*
 * On Solaris and derivatives such as SmartOS, the length of socket options
 * is sizeof(int) for IP_TTL and IPV6_UNICAST_HOPS,
 * so hardcode the size of these options on this platform,
 * and use the general uv__setsockopt_maybe_char call on other platforms.
 */
#if defined(__sun) || defined(_AIX) || defined(__OpenBSD__) || \
    defined(__MVS__)

  return uv__setsockopt(handle,
                        IP_TTL,
                        IPV6_UNICAST_HOPS,
                        &ttl,
                        sizeof(ttl));

#else /* !(defined(__sun) || defined(_AIX) || defined (__OpenBSD__) ||
           defined(__MVS__)) */

  return uv__setsockopt_maybe_char(handle,
                                   IP_TTL,
                                   IPV6_UNICAST_HOPS,
                                   ttl);

#endif /* defined(__sun) || defined(_AIX) || defined (__OpenBSD__) ||
          defined(__MVS__) */
}