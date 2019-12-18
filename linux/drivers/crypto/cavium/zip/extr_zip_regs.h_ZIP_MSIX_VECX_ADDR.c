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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static inline u64 ZIP_MSIX_VECX_ADDR(u64 param1)
{
	if (param1 <= 17)
		return 0x0000838000F00000ull + (param1 & 31) * 0x10ull;
	pr_err("ZIP_MSIX_VECX_ADDR: %llu\n", param1);
	return 0;
}