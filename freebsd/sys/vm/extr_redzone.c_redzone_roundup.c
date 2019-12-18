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
typedef  int u_long ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int REDZONE_HSIZE ; 

__attribute__((used)) static u_long
redzone_roundup(u_long n)
{

	if (n < REDZONE_HSIZE)
		n = REDZONE_HSIZE;
	if (n <= 128)
		return (128);
	else if (n <= 256)
		return (256);
	else if (n <= 512)
		return (512);
	else if (n <= 1024)
		return (1024);
	else if (n <= 2048)
		return (2048);
	return (PAGE_SIZE);
}