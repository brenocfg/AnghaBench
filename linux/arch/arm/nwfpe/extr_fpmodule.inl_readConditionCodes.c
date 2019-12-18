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
 unsigned long CC_MASK ; 
 unsigned long readCPSR () ; 

__attribute__((used)) static inline unsigned long readConditionCodes(void)
{
#ifdef __FPEM_TEST__
	return (0);
#else
	return (readCPSR() & CC_MASK);
#endif
}