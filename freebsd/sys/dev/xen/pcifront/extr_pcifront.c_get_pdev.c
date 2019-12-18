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
struct pcifront_device {int /*<<< orphan*/  ref_cnt; } ;

/* Variables and functions */

__attribute__((used)) static void
get_pdev(struct pcifront_device *pdev)
{
	pdev->ref_cnt++;
}