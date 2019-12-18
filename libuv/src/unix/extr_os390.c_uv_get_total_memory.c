#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  void* data_area_ptr_assign_type ;
struct TYPE_2__ {scalar_t__ deref; void* assign; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ data_area_ptr ;

/* Variables and functions */
 scalar_t__ CVTRCEP_OFFSET ; 
 scalar_t__ CVT_PTR ; 
 scalar_t__ RCEPOOL_OFFSET ; 

uint64_t uv_get_total_memory(void) {
  uint64_t totalram;

  data_area_ptr cvt = {0};
  data_area_ptr rcep = {0};
  cvt.assign = *(data_area_ptr_assign_type*)(CVT_PTR);
  rcep.assign = *(data_area_ptr_assign_type*)(cvt.deref + CVTRCEP_OFFSET);
  totalram = *((uint64_t*)(rcep.deref + RCEPOOL_OFFSET)) * 4;
  return totalram;
}