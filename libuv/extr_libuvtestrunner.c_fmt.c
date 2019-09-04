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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */

const char* fmt(double d) {
  static char buf[1024];
  static char* p;
  uint64_t v;

  if (p == NULL)
    p = buf;

  p += 31;

  if (p >= buf + sizeof(buf))
    return "<buffer too small>";

  v = (uint64_t) d;

#if 0 /* works but we don't care about fractional precision */
  if (d - v >= 0.01) {
    *--p = '0' + (uint64_t) (d * 100) % 10;
    *--p = '0' + (uint64_t) (d * 10) % 10;
    *--p = '.';
  }
#endif

  if (v == 0)
    *--p = '0';

  while (v) {
    if (v) *--p = '0' + (v % 10), v /= 10;
    if (v) *--p = '0' + (v % 10), v /= 10;
    if (v) *--p = '0' + (v % 10), v /= 10;
    if (v) *--p = ',';
  }

  return p;
}