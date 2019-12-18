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
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 long long strtoll (char const*,char**,int) ; 
 long long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_statm (const char *buf, long long *a, int m) {
  static long long page_size = -1;
  if (page_size < 0) {
    page_size = sysconf (_SC_PAGESIZE);
    assert (page_size > 0);
  }
  int i;
  if (m > 7) {
    m = 7;
  }
  const char *p = buf;
  char *q;
  errno = 0;
  for (i = 0; i < m; i++) {
    a[i] = strtoll (p, &q, 10);
    if (p == q || errno) {
      return -1;
    }
    a[i] *= page_size;
    p = q;
  }
  return 0;
}