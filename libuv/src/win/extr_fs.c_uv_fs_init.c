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
struct TYPE_3__ {int /*<<< orphan*/  dwAllocationGranularity; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  uv__allocation_granularity ; 
 int /*<<< orphan*/  uv__fd_hash_init () ; 

void uv_fs_init(void) {
  SYSTEM_INFO system_info;

  GetSystemInfo(&system_info);
  uv__allocation_granularity = system_info.dwAllocationGranularity;

  uv__fd_hash_init();
}