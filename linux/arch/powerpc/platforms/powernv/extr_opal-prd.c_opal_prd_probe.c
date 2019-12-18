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
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  OPAL_MSG_PRD ; 
 int /*<<< orphan*/  OPAL_MSG_PRD2 ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int opal_message_notifier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_message_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_prd_dev ; 
 int /*<<< orphan*/  opal_prd_event_nb ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ prd_node ; 

__attribute__((used)) static int opal_prd_probe(struct platform_device *pdev)
{
	int rc;

	if (!pdev || !pdev->dev.of_node)
		return -ENODEV;

	/* We should only have one prd driver instance per machine; ensure
	 * that we only get a valid probe on a single OF node.
	 */
	if (prd_node)
		return -EBUSY;

	prd_node = pdev->dev.of_node;

	rc = opal_message_notifier_register(OPAL_MSG_PRD, &opal_prd_event_nb);
	if (rc) {
		pr_err("Couldn't register event notifier\n");
		return rc;
	}

	rc = opal_message_notifier_register(OPAL_MSG_PRD2, &opal_prd_event_nb);
	if (rc) {
		pr_err("Couldn't register PRD2 event notifier\n");
		return rc;
	}

	rc = misc_register(&opal_prd_dev);
	if (rc) {
		pr_err("failed to register miscdev\n");
		opal_message_notifier_unregister(OPAL_MSG_PRD,
				&opal_prd_event_nb);
		return rc;
	}

	return 0;
}