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
 unsigned int CACHE_CLR ; 
 int CCR2_L2E ; 
 int /*<<< orphan*/  mb () ; 
 int mfcr_ccr2 () ; 
 int /*<<< orphan*/  mtcr (char*,unsigned int) ; 

__attribute__((used)) static void cache_op_all(unsigned int value, unsigned int l2)
{
	mtcr("cr17", value | CACHE_CLR);
	mb();

	if (l2 && (mfcr_ccr2() & CCR2_L2E)) {
		mtcr("cr24", value | CACHE_CLR);
		mb();
	}
}