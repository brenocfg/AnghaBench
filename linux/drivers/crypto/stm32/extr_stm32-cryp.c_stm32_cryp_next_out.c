#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct stm32_cryp {TYPE_1__* out_sg; int /*<<< orphan*/  out_walk; } ;
struct TYPE_5__ {scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ _walked_out ; 
 int /*<<< orphan*/  scatterwalk_advance (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_start (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* sg_next (TYPE_1__*) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 *stm32_cryp_next_out(struct stm32_cryp *cryp, u32 *dst,
				unsigned int n)
{
	scatterwalk_advance(&cryp->out_walk, n);

	if (unlikely(cryp->out_sg->length == _walked_out)) {
		cryp->out_sg = sg_next(cryp->out_sg);
		if (cryp->out_sg) {
			scatterwalk_start(&cryp->out_walk, cryp->out_sg);
			return (sg_virt(cryp->out_sg) + _walked_out);
		}
	}

	return (u32 *)((u8 *)dst + n);
}