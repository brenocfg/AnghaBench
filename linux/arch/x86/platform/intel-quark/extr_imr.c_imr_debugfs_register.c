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
struct imr_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ *,struct imr_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imr_dbgfs_state_fops ; 

__attribute__((used)) static void imr_debugfs_register(struct imr_device *idev)
{
	debugfs_create_file("imr_state", 0444, NULL, idev,
			    &imr_dbgfs_state_fops);
}