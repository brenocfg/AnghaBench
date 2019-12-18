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
struct TYPE_9__ {scalar_t__* idle_chk_size; int /*<<< orphan*/ ** idle_chk; int /*<<< orphan*/ * idle_chk_dwords; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_2__ qlnx_idle_chk_t ;
struct TYPE_8__ {int num_hwfns; } ;
struct TYPE_10__ {scalar_t__* idle_chk_size; scalar_t__ idle_chk_taken; scalar_t__* idle_chk_dwords; int /*<<< orphan*/ ** idle_chk; TYPE_1__ cdev; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_3__ qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_3__*,char*,int,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int qlnx_idle_chk (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
qlnx_get_idle_chk(qlnx_host_t *ha, qlnx_idle_chk_t *idle_chk)
{
	int		i;
	int		rval = 0;
	uint32_t	dwords = 0;

	idle_chk->pci_func = ha->pci_func;

	for (i = 0; i < ha->cdev.num_hwfns; i++) {

		if ((ha->idle_chk[i] == NULL) ||
				(idle_chk->idle_chk[i] == NULL) ||
				(idle_chk->idle_chk_size[i] <
					ha->idle_chk_size[i]))
			return (EINVAL);

		rval = qlnx_idle_chk(ha, &dwords, i);

		if (rval)
			break;
		
		idle_chk->idle_chk_dwords[i] = dwords;

		QL_DPRINT1(ha,"idle_chk_dwords[%d] = 0x%x\n", i, dwords);

               	rval = copyout(ha->idle_chk[i], idle_chk->idle_chk[i],
				ha->idle_chk_size[i]);

		if (rval)
			break;

		ha->idle_chk_dwords[i] = 0;
	}
	ha->idle_chk_taken = 0;

	return (rval);
}