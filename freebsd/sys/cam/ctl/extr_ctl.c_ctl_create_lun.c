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
struct ctl_be_lun {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  control_softc ; 
 int /*<<< orphan*/  ctl_alloc_lun (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ctl_be_lun*) ; 

__attribute__((used)) static void
ctl_create_lun(struct ctl_be_lun *be_lun)
{

	/*
	 * ctl_alloc_lun() should handle all potential failure cases.
	 */
	ctl_alloc_lun(control_softc, NULL, be_lun);
}