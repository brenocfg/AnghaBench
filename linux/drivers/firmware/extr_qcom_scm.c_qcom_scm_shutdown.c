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

/* Variables and functions */
 scalar_t__ download_mode ; 
 int /*<<< orphan*/  qcom_scm_set_download_mode (int) ; 

__attribute__((used)) static void qcom_scm_shutdown(struct platform_device *pdev)
{
	/* Clean shutdown, disable download mode to allow normal restart */
	if (download_mode)
		qcom_scm_set_download_mode(false);
}