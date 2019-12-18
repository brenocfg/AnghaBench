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
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int QLNXR_CQE_SIZE ; 

__attribute__((used)) static inline int
qlnxr_align_cq_entries(int entries)
{
	u64 size, aligned_size;

	/* We allocate an extra entry that we don't report to the FW.
	 * Why?
	 * The CQE size is 32 bytes but the FW writes in chunks of 64 bytes
	 * (for performance purposes). Allocating an extra entry and telling
	 * the FW we have less prevents overwriting the first entry in case of
	 * a wrap i.e. when the FW writes the last entry and the application
	 * hasn't read the first one.
	 */
	size = (entries + 1) * QLNXR_CQE_SIZE;

	/* We align to PAGE_SIZE.
	 * Why?
	 * Since the CQ is going to be mapped and the mapping is anyhow in whole
	 * kernel pages we benefit from the possibly extra CQEs.
	 */
	aligned_size = ALIGN(size, PAGE_SIZE);

	/* note: for CQs created in user space the result of this function
	 * should match the size mapped in user space
	 */
	return (aligned_size / QLNXR_CQE_SIZE);
}