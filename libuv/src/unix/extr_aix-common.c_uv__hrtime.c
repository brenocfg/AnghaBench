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
typedef  int /*<<< orphan*/  uv_clocktype_t ;
typedef  int uint64_t ;
struct TYPE_4__ {int tb_low; scalar_t__ tb_high; } ;
typedef  TYPE_1__ timebasestruct_t ;

/* Variables and functions */
 int /*<<< orphan*/  TIMEBASE_SZ ; 
 int /*<<< orphan*/  read_wall_time (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_base_to_time (TYPE_1__*,int /*<<< orphan*/ ) ; 

uint64_t uv__hrtime(uv_clocktype_t type) {
  uint64_t G = 1000000000;
  timebasestruct_t t;
  read_wall_time(&t, TIMEBASE_SZ);
  time_base_to_time(&t, TIMEBASE_SZ);
  return (uint64_t) t.tb_high * G + t.tb_low;
}