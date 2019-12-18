#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev_id; } ;
typedef  TYPE_1__ dbdev_tab_t ;

/* Variables and functions */
 TYPE_1__* find_dbdev_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void au1xxx_ddma_del_device(u32 devid)
{
	dbdev_tab_t *p = find_dbdev_id(devid);

	if (p != NULL) {
		memset(p, 0, sizeof(dbdev_tab_t));
		p->dev_id = ~0;
	}
}