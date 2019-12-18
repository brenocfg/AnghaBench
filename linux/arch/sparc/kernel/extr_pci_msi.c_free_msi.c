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
struct pci_pbm_info {int /*<<< orphan*/  msi_bitmap; scalar_t__ msi_first; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_msi(struct pci_pbm_info *pbm, int msi_num)
{
	msi_num -= pbm->msi_first;
	clear_bit(msi_num, pbm->msi_bitmap);
}