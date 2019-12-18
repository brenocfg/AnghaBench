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
typedef  int /*<<< orphan*/  ps_total ;
struct TYPE_3__ {double* loadavg; } ;
typedef  TYPE_1__ perfstat_cpu_total_t ;

/* Variables and functions */
 int SBITS ; 
 int perfstat_cpu_total (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

void uv_loadavg(double avg[3]) {
  perfstat_cpu_total_t ps_total;
  int result = perfstat_cpu_total(NULL, &ps_total, sizeof(ps_total), 1);
  if (result == -1) {
    avg[0] = 0.; avg[1] = 0.; avg[2] = 0.;
    return;
  }
  avg[0] = ps_total.loadavg[0] / (double)(1 << SBITS);
  avg[1] = ps_total.loadavg[1] / (double)(1 << SBITS);
  avg[2] = ps_total.loadavg[2] / (double)(1 << SBITS);
}