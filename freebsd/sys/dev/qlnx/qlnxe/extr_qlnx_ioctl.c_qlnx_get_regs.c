#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_7__ {int num_hwfns; } ;
struct TYPE_8__ {scalar_t__ grcdump_taken; scalar_t__* grcdump_dwords; int /*<<< orphan*/ * grcdump_size; int /*<<< orphan*/ * grcdump; TYPE_1__ cdev; } ;
typedef  TYPE_2__ qlnx_host_t ;
struct TYPE_9__ {scalar_t__ reg_buf_len; int /*<<< orphan*/ * reg_buf; } ;
typedef  TYPE_3__ qlnx_get_regs_t ;

/* Variables and functions */
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qlnx_grc_dump (TYPE_2__*,int*,int) ; 

__attribute__((used)) static int
qlnx_get_regs(qlnx_host_t *ha, qlnx_get_regs_t *regs)
{
	int		i;
	int		rval = 0;
	uint32_t	dwords = 0;
	uint8_t		*outb;

	regs->reg_buf_len = 0;
	outb = regs->reg_buf;

	for (i = 0; i < ha->cdev.num_hwfns; i++) {

		rval = qlnx_grc_dump(ha, &dwords, i);

		if (rval)
			break;

		regs->reg_buf_len += (dwords << 2);

		rval = copyout(ha->grcdump[i], outb, ha->grcdump_size[i]);

		if (rval)
			break;

		ha->grcdump_dwords[i] = 0;
		outb += regs->reg_buf_len;
	}

	ha->grcdump_taken = 0;

	return (rval);
}