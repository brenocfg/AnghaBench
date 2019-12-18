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
struct arm64_ftr_bits {int type; int /*<<< orphan*/  safe_val; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FTR_EXACT 131 
#define  FTR_HIGHER_OR_ZERO_SAFE 130 
#define  FTR_HIGHER_SAFE 129 
#define  FTR_LOWER_SAFE 128 

__attribute__((used)) static s64 arm64_ftr_safe_value(const struct arm64_ftr_bits *ftrp, s64 new,
				s64 cur)
{
	s64 ret = 0;

	switch (ftrp->type) {
	case FTR_EXACT:
		ret = ftrp->safe_val;
		break;
	case FTR_LOWER_SAFE:
		ret = new < cur ? new : cur;
		break;
	case FTR_HIGHER_OR_ZERO_SAFE:
		if (!cur || !new)
			break;
		/* Fallthrough */
	case FTR_HIGHER_SAFE:
		ret = new > cur ? new : cur;
		break;
	default:
		BUG();
	}

	return ret;
}