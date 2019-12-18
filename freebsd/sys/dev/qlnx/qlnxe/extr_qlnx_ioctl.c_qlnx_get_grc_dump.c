#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int num_hwfns; } ;
struct TYPE_9__ {scalar_t__* grcdump_size; scalar_t__ grcdump_taken; scalar_t__* grcdump_dwords; int /*<<< orphan*/ ** grcdump; TYPE_1__ cdev; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_2__ qlnx_host_t ;
struct TYPE_10__ {scalar_t__* grcdump_size; int /*<<< orphan*/ ** grcdump; int /*<<< orphan*/ * grcdump_dwords; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_3__ qlnx_grcdump_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int qlnx_grc_dump (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
qlnx_get_grc_dump(qlnx_host_t *ha, qlnx_grcdump_t *grcdump)
{
	int		i;
	int		rval = 0;
	uint32_t	dwords = 0;

	grcdump->pci_func = ha->pci_func;

	for (i = 0; i < ha->cdev.num_hwfns; i++) {

		if ((ha->grcdump[i] == NULL) || (grcdump->grcdump[i] == NULL) ||
			(grcdump->grcdump_size[i] < ha->grcdump_size[i]))
			return (EINVAL);

		rval = qlnx_grc_dump(ha, &dwords, i);

		if (rval)
			break;

		grcdump->grcdump_dwords[i] = dwords;

		QL_DPRINT1(ha,"grcdump_dwords[%d] = 0x%x\n", i, dwords);

		rval = copyout(ha->grcdump[i], grcdump->grcdump[i],
				ha->grcdump_size[i]);

		if (rval)
			break;

		ha->grcdump_dwords[i] = 0;
	}

	ha->grcdump_taken = 0;

	return (rval);
}