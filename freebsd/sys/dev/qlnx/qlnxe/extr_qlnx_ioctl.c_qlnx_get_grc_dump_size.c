#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int num_hwfns; } ;
struct TYPE_7__ {int /*<<< orphan*/ * grcdump_size; TYPE_1__ cdev; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_2__ qlnx_host_t ;
struct TYPE_8__ {int /*<<< orphan*/ * grcdump_size; int /*<<< orphan*/  pci_func; } ;
typedef  TYPE_3__ qlnx_grcdump_t ;

/* Variables and functions */

__attribute__((used)) static void
qlnx_get_grc_dump_size(qlnx_host_t *ha, qlnx_grcdump_t *grcdump)
{
	int i;

	grcdump->pci_func = ha->pci_func;

	for (i = 0; i < ha->cdev.num_hwfns; i++)
		grcdump->grcdump_size[i] = ha->grcdump_size[i];

	return;
}