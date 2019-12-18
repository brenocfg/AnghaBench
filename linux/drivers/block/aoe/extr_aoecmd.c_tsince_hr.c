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
typedef  int u32 ;
struct frame {int /*<<< orphan*/  sent; } ;

/* Variables and functions */
 int INT_MAX ; 
 int NSEC_PER_USEC ; 
 int UINT_MAX ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
tsince_hr(struct frame *f)
{
	u64 delta = ktime_to_ns(ktime_sub(ktime_get(), f->sent));

	/* delta is normally under 4.2 seconds, avoid 64-bit division */
	if (likely(delta <= UINT_MAX))
		return (u32)delta / NSEC_PER_USEC;

	/* avoid overflow after 71 minutes */
	if (delta > ((u64)INT_MAX * NSEC_PER_USEC))
		return INT_MAX;

	return div_u64(delta, NSEC_PER_USEC);
}