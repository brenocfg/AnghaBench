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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int check_req (struct pci_dev*,int,char*) ; 

__attribute__((used)) static int check_req_msi(struct pci_dev *pdev, int nvec)
{
	return check_req(pdev, nvec, "ibm,req#msi");
}