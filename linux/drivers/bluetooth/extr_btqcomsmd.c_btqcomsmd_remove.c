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
struct platform_device {int dummy; } ;
struct btqcomsmd {int /*<<< orphan*/  acl_channel; int /*<<< orphan*/  cmd_channel; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_free_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_unregister_dev (int /*<<< orphan*/ ) ; 
 struct btqcomsmd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rpmsg_destroy_ept (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btqcomsmd_remove(struct platform_device *pdev)
{
	struct btqcomsmd *btq = platform_get_drvdata(pdev);

	hci_unregister_dev(btq->hdev);
	hci_free_dev(btq->hdev);

	rpmsg_destroy_ept(btq->cmd_channel);
	rpmsg_destroy_ept(btq->acl_channel);

	return 0;
}