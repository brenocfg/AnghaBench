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
struct pfr_addr {int /*<<< orphan*/  pfra_fback; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFR_FB_NONE ; 

__attribute__((used)) static void
pfr_reset_feedback(struct pfr_addr *addr, int size)
{
	struct pfr_addr	*ad;
	int		i;

	for (i = 0, ad = addr; i < size; i++, ad++)
		ad->pfra_fback = PFR_FB_NONE;
}