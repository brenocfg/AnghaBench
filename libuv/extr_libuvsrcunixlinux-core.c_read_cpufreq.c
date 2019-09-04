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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fscanf (int /*<<< orphan*/ *,char*,unsigned long*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/ * uv__open_file (char*) ; 

__attribute__((used)) static unsigned long read_cpufreq(unsigned int cpunum) {
  unsigned long val;
  char buf[1024];
  FILE* fp;

  snprintf(buf,
           sizeof(buf),
           "/sys/devices/system/cpu/cpu%u/cpufreq/scaling_cur_freq",
           cpunum);

  fp = uv__open_file(buf);
  if (fp == NULL)
    return 0;

  if (fscanf(fp, "%lu", &val) != 1)
    val = 0;

  fclose(fp);

  return val;
}