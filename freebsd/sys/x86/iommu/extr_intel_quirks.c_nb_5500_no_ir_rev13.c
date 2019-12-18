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
typedef  int u_int ;
struct dmar_unit {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  nb_no_ir (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int pci_get_revid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nb_5500_no_ir_rev13(struct dmar_unit *unit, device_t nb)
{
	u_int rev_no;

	rev_no = pci_get_revid(nb);
	if (rev_no <= 0x13)
		nb_no_ir(unit, nb);
}