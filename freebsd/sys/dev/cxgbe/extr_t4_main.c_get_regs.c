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
typedef  int /*<<< orphan*/  uint8_t ;
struct t4_regdump {int version; int /*<<< orphan*/  len; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int chip_id (struct adapter*) ; 
 int chip_rev (struct adapter*) ; 
 int /*<<< orphan*/  t4_get_regs (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_regs(struct adapter *sc, struct t4_regdump *regs, uint8_t *buf)
{

	regs->version = chip_id(sc) | chip_rev(sc) << 10;
	t4_get_regs(sc, buf, regs->len);
}