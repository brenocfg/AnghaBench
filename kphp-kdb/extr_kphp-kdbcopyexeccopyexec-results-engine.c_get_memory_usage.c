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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 scalar_t__ close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memset (long long*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int sscanf (char*,char*,long long*) ; 
 long long sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

int get_memory_usage (long long *a, int m) {
  memset (a, 0, sizeof (a[0]) * m);
  char buf[1024], *p;
  int fd = open ("/proc/self/statm", O_RDONLY), n = -1, i;
  if (fd < 0) {
    return -1;
  }
  do {
    n = read (fd, buf, sizeof (buf));
    if (n < 0) {
      if (errno == EINTR) {
        continue;
      }
    }
    break;
  } while (1);

  while (close (fd) < 0 && errno == EINTR) {}

  if (n < 0 || n >= sizeof (buf)) {
    return -1;
  }
  buf[n] = 0;
  vkprintf (3, "/proc/self/statm: %s\n", buf);
  long long page_size = sysconf (_SC_PAGESIZE);
  p = buf;
  for (i = 0; i < m; i++) {
    if (sscanf (p, "%lld", &a[i]) != 1) {
      return -1;
    }
    a[i] *= page_size;
    while (*p && !isspace (*p)) {
      p++;
    }
  }
  return 0;
}