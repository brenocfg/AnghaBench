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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __b15_rac_disable () ; 
 int /*<<< orphan*/  __b15_rac_flush () ; 

__attribute__((used)) static inline u32 b15_rac_disable_and_flush(void)
{
	u32 reg;

	reg = __b15_rac_disable();
	__b15_rac_flush();
	return reg;
}