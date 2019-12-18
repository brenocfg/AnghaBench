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
typedef  int /*<<< orphan*/  processor_info_array_t ;
typedef  int /*<<< orphan*/  processor_cpu_load_info_t ;
typedef  int mach_msg_type_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_fatalError (char*) ; 
 int /*<<< orphan*/  PROCESSOR_CPU_LOAD_INFO ; 
 scalar_t__ host_processor_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mach_host_self () ; 

unsigned ProcessList_allocateCPULoadInfo(processor_cpu_load_info_t *p) {
   mach_msg_type_number_t info_size = sizeof(processor_cpu_load_info_t);
   unsigned cpu_count;

   // TODO Improving the accuracy of the load counts woule help a lot.
   if(0 != host_processor_info(mach_host_self(), PROCESSOR_CPU_LOAD_INFO, &cpu_count, (processor_info_array_t *)p, &info_size)) {
       CRT_fatalError("Unable to retrieve CPU info\n");
   }

   return cpu_count;
}