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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mdl ;

/* Variables and functions */
 void* MmMapLockedPages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
MmMapLockedPagesSpecifyCache(mdl *buf, uint8_t accessmode, uint32_t cachetype,
	void *vaddr, uint32_t bugcheck, uint32_t prio)
{
	return (MmMapLockedPages(buf, accessmode));
}