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
struct xilly_endpoint {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct xilly_endpoint* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  xillybus_endpoint_remove (struct xilly_endpoint*) ; 

__attribute__((used)) static void xilly_remove(struct pci_dev *pdev)
{
	struct xilly_endpoint *endpoint = pci_get_drvdata(pdev);

	xillybus_endpoint_remove(endpoint);
}