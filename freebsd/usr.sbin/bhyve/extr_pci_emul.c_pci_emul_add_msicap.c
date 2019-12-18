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
typedef  int /*<<< orphan*/  u_char ;
struct pci_devinst {int dummy; } ;
struct msicap {int dummy; } ;
typedef  int /*<<< orphan*/  msicap ;

/* Variables and functions */
 int pci_emul_add_capability (struct pci_devinst*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_populate_msicap (struct msicap*,int,int /*<<< orphan*/ ) ; 

int
pci_emul_add_msicap(struct pci_devinst *pi, int msgnum)
{
	struct msicap msicap;

	pci_populate_msicap(&msicap, msgnum, 0);

	return (pci_emul_add_capability(pi, (u_char *)&msicap, sizeof(msicap)));
}