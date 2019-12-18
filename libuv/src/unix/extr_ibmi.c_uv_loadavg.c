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
struct TYPE_3__ {double percent_processing_unit_used; } ;
typedef  TYPE_1__ SSTS0200 ;

/* Variables and functions */
 scalar_t__ get_ibmi_system_status (TYPE_1__*) ; 

void uv_loadavg(double avg[3]) {
  SSTS0200 rcvr;

  if (get_ibmi_system_status(&rcvr)) {
    avg[0] = avg[1] = avg[2] = 0;
    return;
  }

  /* The average (in tenths) of the elapsed time during which the processing
   * units were in use. For example, a value of 411 in binary would be 41.1%.
   * This percentage could be greater than 100% for an uncapped partition.
   */
  double processing_unit_used_percent =
    rcvr.percent_processing_unit_used / 1000.0;

  avg[0] = avg[1] = avg[2] = processing_unit_used_percent;
}