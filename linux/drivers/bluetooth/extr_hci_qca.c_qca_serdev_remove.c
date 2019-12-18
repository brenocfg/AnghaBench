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
struct serdev_device {int dummy; } ;
struct qca_serdev {int /*<<< orphan*/  serdev_hu; int /*<<< orphan*/  susclk; int /*<<< orphan*/  btsoc_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_uart_unregister_device (int /*<<< orphan*/ *) ; 
 scalar_t__ qca_is_wcn399x (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca_power_shutdown (int /*<<< orphan*/ *) ; 
 struct qca_serdev* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static void qca_serdev_remove(struct serdev_device *serdev)
{
	struct qca_serdev *qcadev = serdev_device_get_drvdata(serdev);

	if (qca_is_wcn399x(qcadev->btsoc_type))
		qca_power_shutdown(&qcadev->serdev_hu);
	else
		clk_disable_unprepare(qcadev->susclk);

	hci_uart_unregister_device(&qcadev->serdev_hu);
}