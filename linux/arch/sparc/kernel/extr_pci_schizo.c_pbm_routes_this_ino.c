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
typedef  unsigned long u32 ;
struct pci_pbm_info {unsigned long ino_bitmap; } ;

/* Variables and functions */
 unsigned long IMAP_INO ; 

__attribute__((used)) static int pbm_routes_this_ino(struct pci_pbm_info *pbm, u32 ino)
{
	ino &= IMAP_INO;

	if (pbm->ino_bitmap & (1UL << ino))
		return 1;

	return 0;
}