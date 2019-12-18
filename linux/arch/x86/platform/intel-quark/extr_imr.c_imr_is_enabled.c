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
struct imr_regs {scalar_t__ rmask; scalar_t__ wmask; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;

/* Variables and functions */
 scalar_t__ IMR_READ_ACCESS_ALL ; 
 scalar_t__ IMR_WRITE_ACCESS_ALL ; 
 scalar_t__ imr_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int imr_is_enabled(struct imr_regs *imr)
{
	return !(imr->rmask == IMR_READ_ACCESS_ALL &&
		 imr->wmask == IMR_WRITE_ACCESS_ALL &&
		 imr_to_phys(imr->addr_lo) == 0 &&
		 imr_to_phys(imr->addr_hi) == 0);
}