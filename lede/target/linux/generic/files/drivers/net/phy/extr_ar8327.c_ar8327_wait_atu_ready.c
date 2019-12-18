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
typedef  int /*<<< orphan*/  u16 ;
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8327_ATU_FUNC_BUSY ; 
 int ar8xxx_mii_read32 (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
ar8327_wait_atu_ready(struct ar8xxx_priv *priv, u16 r2, u16 r1)
{
	int timeout = 20;

	while (ar8xxx_mii_read32(priv, r2, r1) & AR8327_ATU_FUNC_BUSY && --timeout) {
		udelay(10);
		cond_resched();
	}

	if (!timeout)
		pr_err("ar8327: timeout waiting for atu to become ready\n");
}