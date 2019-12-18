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
typedef  int u_int ;

/* Variables and functions */
 int MKIMG_VERSION ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void
print_version(void)
{
	u_int width;

#ifdef __LP64__
	width = 64;
#else
	width = 32;
#endif
	printf("mkimg %u (%u-bit)\n", MKIMG_VERSION, width);
}