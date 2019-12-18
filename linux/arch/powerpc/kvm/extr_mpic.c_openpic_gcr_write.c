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
typedef  int uint64_t ;
struct openpic {int gcr; int mpic_mode_mask; } ;

/* Variables and functions */
 int GCR_RESET ; 
 int /*<<< orphan*/  openpic_reset (struct openpic*) ; 

__attribute__((used)) static void openpic_gcr_write(struct openpic *opp, uint64_t val)
{
	if (val & GCR_RESET) {
		openpic_reset(opp);
		return;
	}

	opp->gcr &= ~opp->mpic_mode_mask;
	opp->gcr |= val & opp->mpic_mode_mask;
}