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
typedef  scalar_t__ u32 ;
struct qce_device {int pipe_pair_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  burst_size; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  QCE_BAM_BURST_SIZE ; 
 scalar_t__ QCE_MAJOR_VERSION5 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qce_get_version (struct qce_device*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int qce_check_version(struct qce_device *qce)
{
	u32 major, minor, step;

	qce_get_version(qce, &major, &minor, &step);

	/*
	 * the driver does not support v5 with minor 0 because it has special
	 * alignment requirements.
	 */
	if (major != QCE_MAJOR_VERSION5 || minor == 0)
		return -ENODEV;

	qce->burst_size = QCE_BAM_BURST_SIZE;
	qce->pipe_pair_id = 1;

	dev_dbg(qce->dev, "Crypto device found, version %d.%d.%d\n",
		major, minor, step);

	return 0;
}