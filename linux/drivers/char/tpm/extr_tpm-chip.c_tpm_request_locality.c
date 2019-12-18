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
struct tpm_chip {int locality; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* request_locality ) (struct tpm_chip*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct tpm_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_request_locality(struct tpm_chip *chip)
{
	int rc;

	if (!chip->ops->request_locality)
		return 0;

	rc = chip->ops->request_locality(chip, 0);
	if (rc < 0)
		return rc;

	chip->locality = rc;
	return 0;
}