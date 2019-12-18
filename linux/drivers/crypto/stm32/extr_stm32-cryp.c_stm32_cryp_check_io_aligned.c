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
struct stm32_cryp {int /*<<< orphan*/  hw_blocksize; int /*<<< orphan*/  total_out; int /*<<< orphan*/  out_sg; int /*<<< orphan*/  total_in; int /*<<< orphan*/  in_sg; } ;

/* Variables and functions */
 int stm32_cryp_check_aligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_cryp_check_io_aligned(struct stm32_cryp *cryp)
{
	int ret;

	ret = stm32_cryp_check_aligned(cryp->in_sg, cryp->total_in,
				       cryp->hw_blocksize);
	if (ret)
		return ret;

	ret = stm32_cryp_check_aligned(cryp->out_sg, cryp->total_out,
				       cryp->hw_blocksize);

	return ret;
}