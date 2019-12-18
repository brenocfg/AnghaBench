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
struct lp_struct {int /*<<< orphan*/  dev; int /*<<< orphan*/  bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP_PARPORT_CLAIMED ; 
 int /*<<< orphan*/  parport_claim_or_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lp_claim_parport_or_block(struct lp_struct *this_lp)
{
	if (!test_and_set_bit(LP_PARPORT_CLAIMED, &this_lp->bits)) {
		parport_claim_or_block(this_lp->dev);
	}
}