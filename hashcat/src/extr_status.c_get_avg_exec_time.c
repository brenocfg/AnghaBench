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
struct TYPE_3__ {double* exec_msec; scalar_t__ exec_pos; } ;
typedef  TYPE_1__ hc_device_param_t ;

/* Variables and functions */
 int EXEC_CACHE ; 

double get_avg_exec_time (hc_device_param_t *device_param, const int last_num_entries)
{
  int exec_pos = (int) device_param->exec_pos - last_num_entries;

  if (exec_pos < 0) exec_pos += EXEC_CACHE;

  double exec_msec_sum = 0;

  int exec_msec_cnt = 0;

  for (int i = 0; i < last_num_entries; i++)
  {
    double exec_msec = device_param->exec_msec[(exec_pos + i) % EXEC_CACHE];

    if (exec_msec > 0)
    {
      exec_msec_sum += exec_msec;

      exec_msec_cnt++;
    }
  }

  if (exec_msec_cnt == 0) return 0;

  return exec_msec_sum / exec_msec_cnt;
}