#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tpm_chip {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* clk_enable ) (struct tpm_chip*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct tpm_chip*,int) ; 

__attribute__((used)) static void tpm_clk_disable(struct tpm_chip *chip)
{
	if (chip->ops->clk_enable)
		chip->ops->clk_enable(chip, false);
}