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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int CTL_HW ; 
 int HW_PHYSMEM ; 
 int HW_PHYSMEM64 ; 
 int /*<<< orphan*/  UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sysctl (int*,int,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint64_t uv_get_total_memory(void) {
#if defined(HW_PHYSMEM64)
  uint64_t info;
  int which[] = {CTL_HW, HW_PHYSMEM64};
#else
  unsigned int info;
  int which[] = {CTL_HW, HW_PHYSMEM};
#endif
  size_t size = sizeof(info);

  if (sysctl(which, 2, &info, &size, NULL, 0))
    return UV__ERR(errno);

  return (uint64_t) info;
}