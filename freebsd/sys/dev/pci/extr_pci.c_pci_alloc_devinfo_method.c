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
struct pci_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct pci_devinfo* malloc (int,int /*<<< orphan*/ ,int) ; 

struct pci_devinfo *
pci_alloc_devinfo_method(device_t dev)
{

	return (malloc(sizeof(struct pci_devinfo), M_DEVBUF,
	    M_WAITOK | M_ZERO));
}