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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int memlowercmp (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int
memcanoncmp(uint8_t* p1, uint8_t len1, uint8_t* p2, uint8_t len2)
{
	uint8_t min = (len1<len2)?len1:len2;
	int c = memlowercmp(p1, p2, min);
	if(c != 0)
		return c;
	/* equal, see who is shortest */
	if(len1 < len2)
		return -1;
	if(len1 > len2)
		return 1;
	return 0;
}