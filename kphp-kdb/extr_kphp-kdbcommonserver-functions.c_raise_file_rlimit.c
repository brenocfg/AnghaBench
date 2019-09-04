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
struct rlimit {int rlim_cur; int rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 scalar_t__ getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 

int raise_file_rlimit (int maxfiles) {
  struct rlimit rlim;
  
  if (getrlimit(RLIMIT_NOFILE, &rlim) != 0) {
    kprintf ("failed to getrlimit number of files\n");
    return -1;
  } else {
    if (rlim.rlim_cur < maxfiles)
      rlim.rlim_cur = maxfiles + 3;
    if (rlim.rlim_max < rlim.rlim_cur)
      rlim.rlim_max = rlim.rlim_cur;
    if (setrlimit(RLIMIT_NOFILE, &rlim) != 0) {
      kprintf ("failed to set rlimit for open files. Try running as root or requesting smaller maxconns value.\n");
      return -1;
    }
  }
  return 0;
}