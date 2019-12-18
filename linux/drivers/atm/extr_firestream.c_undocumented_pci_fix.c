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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 

__attribute__((used)) static void undocumented_pci_fix(struct pci_dev *pdev)
{
	u32 tint;

	/* The Windows driver says: */
	/* Switch off FireStream Retry Limit Threshold 
	 */

	/* The register at 0x28 is documented as "reserved", no further
	   comments. */

	pci_read_config_dword (pdev, 0x28, &tint);
	if (tint != 0x80) {
		tint = 0x80;
		pci_write_config_dword (pdev, 0x28, tint);
	}
}