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
 int /*<<< orphan*/  SPRN_IAMR ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_execute_disable_supported ; 

__attribute__((used)) static inline u64 read_iamr(void)
{
	if (!likely(pkey_execute_disable_supported))
		return 0x0UL;

	return mfspr(SPRN_IAMR);
}