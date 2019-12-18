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
struct __prci_wrpll_data {int /*<<< orphan*/  cfg0_offs; int /*<<< orphan*/  c; } ;
struct __prci_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __prci_readl (struct __prci_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __prci_wrpll_unpack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __prci_wrpll_read_cfg(struct __prci_data *pd,
				  struct __prci_wrpll_data *pwd)
{
	__prci_wrpll_unpack(&pwd->c, __prci_readl(pd, pwd->cfg0_offs));
}