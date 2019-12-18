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
struct atmel_tdes_dev {int flags; scalar_t__ err; int /*<<< orphan*/  iclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDES_CR ; 
 int /*<<< orphan*/  TDES_CR_SWRST ; 
 int TDES_FLAGS_INIT ; 
 int /*<<< orphan*/  atmel_tdes_write (struct atmel_tdes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_tdes_hw_init(struct atmel_tdes_dev *dd)
{
	int err;

	err = clk_prepare_enable(dd->iclk);
	if (err)
		return err;

	if (!(dd->flags & TDES_FLAGS_INIT)) {
		atmel_tdes_write(dd, TDES_CR, TDES_CR_SWRST);
		dd->flags |= TDES_FLAGS_INIT;
		dd->err = 0;
	}

	return 0;
}