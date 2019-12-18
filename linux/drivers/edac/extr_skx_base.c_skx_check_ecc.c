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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SKX_GET_MTMTR (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool skx_check_ecc(struct pci_dev *pdev)
{
	u32 mtmtr;

	SKX_GET_MTMTR(pdev, mtmtr);

	return !!GET_BITFIELD(mtmtr, 2, 2);
}