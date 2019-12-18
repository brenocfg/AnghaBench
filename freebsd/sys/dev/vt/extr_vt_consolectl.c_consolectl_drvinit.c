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

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  VTY_VT ; 
 int /*<<< orphan*/  consolectl_cdevsw ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
consolectl_drvinit(void *unused)
{

	if (!vty_enabled(VTY_VT))
		return;
	make_dev(&consolectl_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600,
	    "consolectl");
}