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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
#define  CTL_KERN 129 
#define  KERN_ARND 128 
 int UV_EIO ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int sysctl (int*,int /*<<< orphan*/ ,unsigned char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uv__random_sysctl(void* buf, size_t len) {
  static int name[] = {CTL_KERN, KERN_ARND};
  size_t count, req;
  unsigned char* p;

  p = buf;
  while (len) {
    req = len < 32 ? len : 32;
    count = req;

    if (sysctl(name, ARRAY_SIZE(name), p, &count, NULL, 0) == -1)
      return UV__ERR(errno);

    if (count != req)
      return UV_EIO;  /* Can't happen. */

    p += count;
    len -= count;
  }

  return 0;
}