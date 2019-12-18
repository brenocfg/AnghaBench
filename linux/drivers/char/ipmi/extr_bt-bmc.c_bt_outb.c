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
typedef  int /*<<< orphan*/  u8 ;
struct bt_bmc {scalar_t__ offset; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt_outb(struct bt_bmc *bt_bmc, u8 data, int reg)
{
	int rc;

	rc = regmap_write(bt_bmc->map, bt_bmc->offset + reg, data);
	WARN(rc != 0, "regmap_write() failed: %d\n", rc);
}