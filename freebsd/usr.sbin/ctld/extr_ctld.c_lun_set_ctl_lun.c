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
typedef  int /*<<< orphan*/  uint32_t ;
struct lun {int /*<<< orphan*/  l_ctl_lun; } ;

/* Variables and functions */

void
lun_set_ctl_lun(struct lun *lun, uint32_t value)
{

	lun->l_ctl_lun = value;
}