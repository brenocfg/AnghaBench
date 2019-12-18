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
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  host_info_t ;
typedef  int /*<<< orphan*/  host_basic_info_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_fatalError (char*) ; 
 int /*<<< orphan*/  HOST_BASIC_INFO ; 
 int /*<<< orphan*/  HOST_BASIC_INFO_COUNT ; 
 scalar_t__ host_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_host_self () ; 

void ProcessList_getHostInfo(host_basic_info_data_t *p) {
   mach_msg_type_number_t info_size = HOST_BASIC_INFO_COUNT;

   if(0 != host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)p, &info_size)) {
       CRT_fatalError("Unable to retrieve host info\n");
   }
}