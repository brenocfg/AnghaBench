#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fw_unit {int /*<<< orphan*/ * directory; } ;
struct TYPE_2__ {int /*<<< orphan*/ * config_rom; } ;

/* Variables and functions */
 TYPE_1__* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  get_ids (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void get_modalias_ids(struct fw_unit *unit, int *id)
{
	get_ids(&fw_parent_device(unit)->config_rom[5], id);
	get_ids(unit->directory, id);
}