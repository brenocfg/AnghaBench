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
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 int UV_EINVAL ; 
 int UV_ENOTSUP ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 int uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_udp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int uv_udp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_udp_set_broadcast (int /*<<< orphan*/ *,int) ; 
 int uv_udp_set_multicast_loop (int /*<<< orphan*/ *,int) ; 
 int uv_udp_set_multicast_ttl (int /*<<< orphan*/ *,int) ; 
 int uv_udp_set_ttl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udp_options_test(const struct sockaddr* addr) {
  static int invalid_ttls[] = { -1, 0, 256 };
  uv_loop_t* loop;
  uv_udp_t h;
  int i, r;

  loop = uv_default_loop();

  r = uv_udp_init(loop, &h);
  ASSERT(r == 0);

  uv_unref((uv_handle_t*)&h); /* don't keep the loop alive */

  r = uv_udp_bind(&h, addr, 0);
  ASSERT(r == 0);

  r = uv_udp_set_broadcast(&h, 1);
  r |= uv_udp_set_broadcast(&h, 1);
  r |= uv_udp_set_broadcast(&h, 0);
  r |= uv_udp_set_broadcast(&h, 0);
  ASSERT(r == 0);

  /* values 1-255 should work */
  for (i = 1; i <= 255; i++) {
    r = uv_udp_set_ttl(&h, i);
#if defined(__MVS__)
    if (addr->sa_family == AF_INET6)
      ASSERT(r == 0);
    else
      ASSERT(r == UV_ENOTSUP);
#else
    ASSERT(r == 0);
#endif
  }

  for (i = 0; i < (int) ARRAY_SIZE(invalid_ttls); i++) {
    r = uv_udp_set_ttl(&h, invalid_ttls[i]);
    ASSERT(r == UV_EINVAL);
  }

  r = uv_udp_set_multicast_loop(&h, 1);
  r |= uv_udp_set_multicast_loop(&h, 1);
  r |= uv_udp_set_multicast_loop(&h, 0);
  r |= uv_udp_set_multicast_loop(&h, 0);
  ASSERT(r == 0);

  /* values 0-255 should work */
  for (i = 0; i <= 255; i++) {
    r = uv_udp_set_multicast_ttl(&h, i);
    ASSERT(r == 0);
  }

  /* anything >255 should fail */
  r = uv_udp_set_multicast_ttl(&h, 256);
  ASSERT(r == UV_EINVAL);
  /* don't test ttl=-1, it's a valid value on some platforms */

  r = uv_run(loop, UV_RUN_DEFAULT);
  ASSERT(r == 0);

  MAKE_VALGRIND_HAPPY();
  return 0;
}