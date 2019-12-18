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
struct mc5 {int /*<<< orphan*/  parity_enabled; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MC5_DB_CONFIG ; 
 int /*<<< orphan*/  F_DBGIEN ; 
 int F_MBUSEN ; 
 int V_PRTYEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mc5_dbgi_mode_disable(const struct mc5 *mc5)
{
	t3_set_reg_field(mc5->adapter, A_MC5_DB_CONFIG, F_DBGIEN,
			 V_PRTYEN(mc5->parity_enabled) | F_MBUSEN);
}