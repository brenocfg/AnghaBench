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
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int UV_EINVAL ; 
 int uv__setsockopt (int /*<<< orphan*/ *,int,int,int*,int) ; 

__attribute__((used)) static int uv__setsockopt_maybe_char(uv_udp_t* handle,
                                     int option4,
                                     int option6,
                                     int val) {
#if defined(__sun) || defined(_AIX) || defined(__MVS__)
  char arg = val;
#elif defined(__OpenBSD__)
  unsigned char arg = val;
#else
  int arg = val;
#endif

  if (val < 0 || val > 255)
    return UV_EINVAL;

  return uv__setsockopt(handle, option4, option6, &arg, sizeof(arg));
}