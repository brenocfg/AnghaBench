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
struct mtd_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mtd_info** concat_devs ; 
 int /*<<< orphan*/  mtd_concat_add_work ; 
 int /*<<< orphan*/  mtd_concat_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mtd_concat_add(struct mtd_info *mtd)
{
	static bool registered = false;

	if (registered)
		return;

	if (!strcmp(mtd->name, "spi0.0"))
		concat_devs[0] = mtd;
	else if (!strcmp(mtd->name, "spi0.1"))
		concat_devs[1] = mtd;
	else
		return;

	if (!concat_devs[0] || !concat_devs[1])
		return;

	registered = true;
	INIT_WORK(&mtd_concat_work, mtd_concat_add_work);
	schedule_work(&mtd_concat_work);
}