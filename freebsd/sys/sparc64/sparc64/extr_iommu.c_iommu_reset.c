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
typedef  unsigned long long uint64_t ;
struct iommu_state {unsigned long long is_ptsb; int is_flags; unsigned long long is_tsbsize; unsigned long long is_cr; scalar_t__* is_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMR_CACHE_INVAL ; 
 int /*<<< orphan*/  IMR_CTL ; 
 int /*<<< orphan*/  IMR_TSB ; 
 int IOMMU_FIRE ; 
 unsigned long long IOMMU_READ8 (struct iommu_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IOMMU_RERUN_DISABLE ; 
 int /*<<< orphan*/  IOMMU_WRITE8 (struct iommu_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ISR_CTL ; 
 unsigned long long STRBUF_EN ; 
 unsigned long long STRBUF_RR_DIS ; 
 int /*<<< orphan*/  is_iommu ; 
 int /*<<< orphan*/ * is_sb ; 

void
iommu_reset(struct iommu_state *is)
{
	uint64_t tsb;
	int i;

	tsb = is->is_ptsb;
	if ((is->is_flags & IOMMU_FIRE) != 0) {
		tsb |= is->is_tsbsize;
		IOMMU_WRITE8(is, is_iommu, IMR_CACHE_INVAL, ~0ULL);
	}
	IOMMU_WRITE8(is, is_iommu, IMR_TSB, tsb);
	IOMMU_WRITE8(is, is_iommu, IMR_CTL, is->is_cr);

	for (i = 0; i < 2; i++) {
		if (is->is_sb[i] != 0) {
			IOMMU_WRITE8(is, is_sb[i], ISR_CTL, STRBUF_EN |
			    ((is->is_flags & IOMMU_RERUN_DISABLE) != 0 ?
			    STRBUF_RR_DIS : 0));

			/* No streaming buffers?  Disable them. */
			if ((IOMMU_READ8(is, is_sb[i], ISR_CTL) &
			    STRBUF_EN) == 0)
				is->is_sb[i] = 0;
		}
	}

	(void)IOMMU_READ8(is, is_iommu, IMR_CTL);
}