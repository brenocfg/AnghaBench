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
struct TYPE_3__ {int real_free; } ;
typedef  TYPE_1__ perfstat_memory_total_t ;
typedef  int /*<<< orphan*/  mem_total ;

/* Variables and functions */
 int perfstat_memory_total (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

uint64_t uv_get_free_memory(void) {
  perfstat_memory_total_t mem_total;
  int result = perfstat_memory_total(NULL, &mem_total, sizeof(mem_total), 1);
  if (result == -1) {
    return 0;
  }
  return mem_total.real_free * 4096;
}