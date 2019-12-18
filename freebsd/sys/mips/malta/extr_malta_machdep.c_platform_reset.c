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
 char MALTA_GORESET ; 
 int /*<<< orphan*/  MALTA_SOFTRES ; 
 scalar_t__ MIPS_PHYS_TO_KSEG0 (int /*<<< orphan*/ ) ; 

void
platform_reset(void)
{
	char *c;

	c = (char *)MIPS_PHYS_TO_KSEG0(MALTA_SOFTRES);
	*c = MALTA_GORESET;
}