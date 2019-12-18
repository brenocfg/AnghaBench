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
struct lanai_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int sram_test_pass (struct lanai_dev const*,int) ; 

__attribute__((used)) static int sram_test_and_clear(const struct lanai_dev *lanai)
{
#ifdef FULL_MEMORY_TEST
	int result;
	DPRINTK("testing SRAM\n");
	if ((result = sram_test_pass(lanai, 0x5555)) != 0)
		return result;
	if ((result = sram_test_pass(lanai, 0xAAAA)) != 0)
		return result;
#endif
	DPRINTK("clearing SRAM\n");
	return sram_test_pass(lanai, 0x0000);
}