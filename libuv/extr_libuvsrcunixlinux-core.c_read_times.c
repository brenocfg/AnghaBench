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
struct uv_cpu_times_s {unsigned long user; unsigned long nice; unsigned long sys; unsigned long idle; unsigned long irq; } ;
struct TYPE_3__ {struct uv_cpu_times_s cpu_times; } ;
typedef  TYPE_1__ uv_cpu_info_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_CLK_TCK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,...) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 unsigned long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_times(FILE* statfile_fp,
                      unsigned int numcpus,
                      uv_cpu_info_t* ci) {
  unsigned long clock_ticks;
  struct uv_cpu_times_s ts;
  unsigned long user;
  unsigned long nice;
  unsigned long sys;
  unsigned long idle;
  unsigned long dummy;
  unsigned long irq;
  unsigned int num;
  unsigned int len;
  char buf[1024];

  clock_ticks = sysconf(_SC_CLK_TCK);
  assert(clock_ticks != (unsigned long) -1);
  assert(clock_ticks != 0);

  rewind(statfile_fp);

  if (!fgets(buf, sizeof(buf), statfile_fp))
    abort();

  num = 0;

  while (fgets(buf, sizeof(buf), statfile_fp)) {
    if (num >= numcpus)
      break;

    if (strncmp(buf, "cpu", 3))
      break;

    /* skip "cpu<num> " marker */
    {
      unsigned int n;
      int r = sscanf(buf, "cpu%u ", &n);
      assert(r == 1);
      (void) r;  /* silence build warning */
      for (len = sizeof("cpu0"); n /= 10; len++);
    }

    /* Line contains user, nice, system, idle, iowait, irq, softirq, steal,
     * guest, guest_nice but we're only interested in the first four + irq.
     *
     * Don't use %*s to skip fields or %ll to read straight into the uint64_t
     * fields, they're not allowed in C89 mode.
     */
    if (6 != sscanf(buf + len,
                    "%lu %lu %lu %lu %lu %lu",
                    &user,
                    &nice,
                    &sys,
                    &idle,
                    &dummy,
                    &irq))
      abort();

    ts.user = clock_ticks * user;
    ts.nice = clock_ticks * nice;
    ts.sys  = clock_ticks * sys;
    ts.idle = clock_ticks * idle;
    ts.irq  = clock_ticks * irq;
    ci[num++].cpu_times = ts;
  }
  assert(num == numcpus);

  return 0;
}