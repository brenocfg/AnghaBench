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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int TARGET_PTR_BIT ; 
 int /*<<< orphan*/  extract_unsigned_integer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static CORE_ADDR
read_pointer (CORE_ADDR address)
{
	CORE_ADDR value;

	if (target_read_memory(address, (char *)&value, TARGET_PTR_BIT / 8) !=
	    0)
		return (0);	
	return (extract_unsigned_integer(&value, TARGET_PTR_BIT / 8));
}