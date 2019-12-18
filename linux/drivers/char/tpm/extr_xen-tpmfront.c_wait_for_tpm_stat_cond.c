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
typedef  int u8 ;
struct tpm_chip {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* status ) (struct tpm_chip*) ;scalar_t__ (* req_canceled ) (struct tpm_chip*,int) ;} ;

/* Variables and functions */
 int stub1 (struct tpm_chip*) ; 
 scalar_t__ stub2 (struct tpm_chip*,int) ; 

__attribute__((used)) static bool wait_for_tpm_stat_cond(struct tpm_chip *chip, u8 mask,
					bool check_cancel, bool *canceled)
{
	u8 status = chip->ops->status(chip);

	*canceled = false;
	if ((status & mask) == mask)
		return true;
	if (check_cancel && chip->ops->req_canceled(chip, status)) {
		*canceled = true;
		return true;
	}
	return false;
}