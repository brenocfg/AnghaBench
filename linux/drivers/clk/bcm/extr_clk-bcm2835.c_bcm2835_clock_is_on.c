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
struct clk_hw {int dummy; } ;
struct bcm2835_cprman {int dummy; } ;
struct bcm2835_clock_data {int /*<<< orphan*/  ctl_reg; } ;
struct bcm2835_clock {struct bcm2835_clock_data* data; struct bcm2835_cprman* cprman; } ;

/* Variables and functions */
 int CM_ENABLE ; 
 struct bcm2835_clock* bcm2835_clock_from_hw (struct clk_hw*) ; 
 int cprman_read (struct bcm2835_cprman*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_clock_is_on(struct clk_hw *hw)
{
	struct bcm2835_clock *clock = bcm2835_clock_from_hw(hw);
	struct bcm2835_cprman *cprman = clock->cprman;
	const struct bcm2835_clock_data *data = clock->data;

	return (cprman_read(cprman, data->ctl_reg) & CM_ENABLE) != 0;
}