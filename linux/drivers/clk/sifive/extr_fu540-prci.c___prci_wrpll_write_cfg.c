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
struct wrpll_cfg {int dummy; } ;
struct __prci_wrpll_data {int /*<<< orphan*/  c; int /*<<< orphan*/  cfg0_offs; } ;
struct __prci_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __prci_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct __prci_data*) ; 
 int /*<<< orphan*/  __prci_wrpll_pack (struct wrpll_cfg*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct wrpll_cfg*,int) ; 

__attribute__((used)) static void __prci_wrpll_write_cfg(struct __prci_data *pd,
				   struct __prci_wrpll_data *pwd,
				   struct wrpll_cfg *c)
{
	__prci_writel(__prci_wrpll_pack(c), pwd->cfg0_offs, pd);

	memcpy(&pwd->c, c, sizeof(*c));
}