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

/* Variables and functions */
 int atoi (char const*) ; 
 char* gnu_get_libc_version () ; 
 int platform_needs_custom_semaphore ; 

__attribute__((used)) static void glibc_version_check(void) {
  const char* version = gnu_get_libc_version();
  platform_needs_custom_semaphore =
      version[0] == '2' && version[1] == '.' &&
      atoi(version + 2) < 21;
}