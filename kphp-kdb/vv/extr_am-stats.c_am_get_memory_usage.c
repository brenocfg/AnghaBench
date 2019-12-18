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
typedef  int /*<<< orphan*/  proc_filename ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int parse_statm (char*,long long*,int) ; 
 scalar_t__ read_whole_file (char*,char*,int) ; 
 int snprintf (char*,int,char*,int) ; 

int am_get_memory_usage (pid_t pid, long long *a, int m) {
  char proc_filename[32];
  char buf[4096];
  assert (snprintf (proc_filename, sizeof (proc_filename), "/proc/%d/statm",  (int) pid) < sizeof (proc_filename));
  if (read_whole_file (proc_filename, buf, sizeof (buf)) < 0) {
    return -1;
  }
  return parse_statm (buf, a, m);
}