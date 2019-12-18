#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct hisi_qm {TYPE_2__* ops; TYPE_1__* pdev; } ;
struct TYPE_4__ {int (* get_vft ) (struct hisi_qm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct hisi_qm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int hisi_qm_get_vft(struct hisi_qm *qm, u32 *base, u32 *number)
{
	if (!base || !number)
		return -EINVAL;

	if (!qm->ops->get_vft) {
		dev_err(&qm->pdev->dev, "Don't support vft read!\n");
		return -EINVAL;
	}

	return qm->ops->get_vft(qm, base, number);
}