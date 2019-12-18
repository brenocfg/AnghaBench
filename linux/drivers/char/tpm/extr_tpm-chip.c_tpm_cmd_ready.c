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
struct TYPE_2__ {int (* cmd_ready ) (struct tpm_chip*) ;} ;

/* Variables and functions */
 int stub1 (struct tpm_chip*) ; 

__attribute__((used)) static int tpm_cmd_ready(struct tpm_chip *chip)
{
	if (!chip->ops->cmd_ready)
		return 0;

	return chip->ops->cmd_ready(chip);
}