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
struct hci_uart {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 struct hci_uart* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  qca_power_shutdown (struct hci_uart*) ; 
 int /*<<< orphan*/  qca_send_pre_shutdown_cmd (struct hci_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int qca_power_off(struct hci_dev *hdev)
{
	struct hci_uart *hu = hci_get_drvdata(hdev);

	/* Perform pre shutdown command */
	qca_send_pre_shutdown_cmd(hdev);

	usleep_range(8000, 10000);

	qca_power_shutdown(hu);
	return 0;
}