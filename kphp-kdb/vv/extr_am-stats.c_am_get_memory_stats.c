#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {long long vm_size; long long vm_rss; long long vm_data; long long mem_free; long long swap_total; long long swap_free; long long swap_used; } ;
typedef  TYPE_1__ am_memory_stat_t ;

/* Variables and functions */
 int AM_GET_MEMORY_USAGE_OVERALL ; 
 int AM_GET_MEMORY_USAGE_SELF ; 
 scalar_t__ am_get_memory_usage (int /*<<< orphan*/ ,long long*,int) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_whole_file (char*,char*,int) ; 
 int sscanf (char*,char*,char*,long long*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  vkprintf (int,char*,char*) ; 

int am_get_memory_stats (am_memory_stat_t *S, int flags) {
  if (!flags) {
    return -1;
  }
  long long a[6];
  memset (S, 0, sizeof (*S));

  if (flags & AM_GET_MEMORY_USAGE_SELF) {
    if (am_get_memory_usage (getpid (), a, 6) < 0) {
      return -1;
    }
    S->vm_size = a[0];
    S->vm_rss = a[1];
    S->vm_data = a[5];
  }

  if (flags & AM_GET_MEMORY_USAGE_OVERALL) {
    char buf[16384], *p;
    if (read_whole_file ("/proc/meminfo", buf, sizeof (buf)) < 0) {
      return -1;
    }
    vkprintf (4, "/proc/meminfo: %s\n", buf);
    char key[32], suffix[32];
    long long value;
    int r = 0;
    for (p = strtok (buf, "\n"); p != NULL; p = strtok (NULL, "\n")) {
      if (sscanf (p, "%31s%lld%31s", key, &value, suffix) == 3 && !strcmp (suffix, "kB")) {
        if (!strcmp (key, "MemFree:")) {
          S->mem_free = value << 10;
          r |= 1;
        } else if (!strcmp (key, "SwapTotal:")) {
          S->swap_total = value << 10;
          r |= 2;
        } else if (!strcmp (key, "SwapFree:")) {
          S->swap_free = value << 10;
          r |= 4;
        }
      }
    }
    if (r != 7) {
      return -1;
    }
    S->swap_used = S->swap_total - S->swap_free;
  }
  return 0;
}