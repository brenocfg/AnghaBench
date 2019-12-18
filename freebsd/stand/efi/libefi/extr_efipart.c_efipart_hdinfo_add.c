#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * pd_devsw; scalar_t__ pd_unit; } ;
typedef  TYPE_1__ pdinfo_t ;
typedef  int /*<<< orphan*/  EFI_DEVICE_PATH ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* STAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efipart_hddev ; 
 scalar_t__ efipart_hdinfo_add_node (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdinfo ; 
 int /*<<< orphan*/  pd_link ; 
 int /*<<< orphan*/  pdinfo ; 

__attribute__((used)) static void
efipart_hdinfo_add(pdinfo_t *hd, EFI_DEVICE_PATH *node)
{
	pdinfo_t *last;

	if (efipart_hdinfo_add_node(hd, node))
		return;

	last = STAILQ_LAST(&hdinfo, pdinfo, pd_link);
	if (last != NULL)
		hd->pd_unit = last->pd_unit + 1;
	else
		hd->pd_unit = 0;

	/* Add the disk. */
	hd->pd_devsw = &efipart_hddev;
	STAILQ_INSERT_TAIL(&hdinfo, hd, pd_link);
}