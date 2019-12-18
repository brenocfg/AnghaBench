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
typedef  int /*<<< orphan*/ * processor_cpu_load_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_fatalError (char*) ; 
 scalar_t__ munmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_size ; 

void ProcessList_freeCPULoadInfo(processor_cpu_load_info_t *p) {
   if(NULL != p && NULL != *p) {
       if(0 != munmap(*p, vm_page_size)) {
           CRT_fatalError("Unable to free old CPU load information\n");
       }
       *p = NULL;
   }
}