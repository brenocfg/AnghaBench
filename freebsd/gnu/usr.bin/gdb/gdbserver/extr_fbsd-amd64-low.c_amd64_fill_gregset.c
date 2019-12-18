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
 int AMD64_NUM_REGS ; 
 int* amd64_regmap ; 
 int /*<<< orphan*/  collect_register (int,char*) ; 

__attribute__((used)) static void
amd64_fill_gregset(void *buf)
{
	int i;

	for (i = 0; i < AMD64_NUM_REGS; i++)
		collect_register(i, ((char *)buf) + amd64_regmap[i]);
}