#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {unsigned long long vm_peak; unsigned long long vm; unsigned long long rss_peak; unsigned long long rss; } ;
typedef  TYPE_1__ mem_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int TMEM_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 
 int /*<<< orphan*/  sscanf (char*,char*,unsigned long long*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int get_mem_stats (pid_t pid, mem_info_t *info) {
#define TMEM_SIZE 10000
  static char mem[TMEM_SIZE];
  snprintf (mem, TMEM_SIZE, "/proc/%lu/status", (unsigned long)pid);
  int fd = open (mem, O_RDONLY);

  if (fd == -1) {
    return 0;
  }

  int size = (int)read (fd, mem, TMEM_SIZE - 1);
  if (size <= 0) {
    close (fd);
    return 0;
  }
  mem[size] = 0;

  char *s = mem;
  while (*s) {
    char *st = s;
    while (*s != 0 && *s != '\n') {
      s++;
    }
    unsigned long long *x = NULL;
    if (strncmp (st, "VmPeak", 6) == 0) {
      x = &info->vm_peak;
    }
    if (strncmp (st, "VmSize", 6) == 0) {
      x = &info->vm;
    }
    if (strncmp (st, "VmHWM", 5) == 0) {
      x = &info->rss_peak;
    }
    if (strncmp (st, "VmRSS", 5) == 0) {
      x = &info->rss;
    }
    if (x != NULL) {
      while (st < s && *st != ' ') {
        st++;
      }
      *x = (unsigned long long)-1;

      if (st < s) {
        sscanf (st, "%llu", x);
      }
    }
    if (*s == 0) {
      break;
    }
    s++;
  }

  close (fd);
  return 1;
#undef TMEM_SIZE
}