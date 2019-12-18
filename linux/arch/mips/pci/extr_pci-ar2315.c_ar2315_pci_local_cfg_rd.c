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
typedef  int /*<<< orphan*/  u32 ;
struct ar2315_pci_ctrl {int dummy; } ;

/* Variables and functions */
 int ar2315_pci_cfg_access (struct ar2315_pci_ctrl*,unsigned int,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int ar2315_pci_local_cfg_rd(struct ar2315_pci_ctrl *apc,
					  unsigned devfn, int where, u32 *val)
{
	return ar2315_pci_cfg_access(apc, devfn, where, sizeof(u32), val,
				     false);
}