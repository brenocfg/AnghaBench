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
typedef  int /*<<< orphan*/  maxPid ;

/* Variables and functions */
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int Platform_getMaxPid() {
   int maxPid;
   size_t size = sizeof(maxPid);
   int err = sysctlbyname("kern.pid_max", &maxPid, &size, NULL, 0);
   if (err) {
      return 999999;
   }
   return maxPid;
}