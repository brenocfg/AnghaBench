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
 scalar_t__ FALSE ; 
 int UV_EIO ; 
 int UV_ENOSYS ; 
 scalar_t__ pRtlGenRandom (void*,size_t) ; 

int uv__random_rtlgenrandom(void* buf, size_t buflen) {
  if (pRtlGenRandom == NULL)
    return UV_ENOSYS;

  if (buflen == 0)
    return 0;

  if (pRtlGenRandom(buf, buflen) == FALSE)
    return UV_EIO;

  return 0;
}