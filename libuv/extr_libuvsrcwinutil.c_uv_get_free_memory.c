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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  memory_status ;
struct TYPE_3__ {int dwLength; int /*<<< orphan*/  ullAvailPhys; } ;
typedef  TYPE_1__ MEMORYSTATUSEX ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalMemoryStatusEx (TYPE_1__*) ; 

uint64_t uv_get_free_memory(void) {
  MEMORYSTATUSEX memory_status;
  memory_status.dwLength = sizeof(memory_status);

  if (!GlobalMemoryStatusEx(&memory_status)) {
     return -1;
  }

  return (uint64_t)memory_status.ullAvailPhys;
}