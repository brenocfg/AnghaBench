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
typedef  int uint16_t ;
struct pci_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int REG (int /*<<< orphan*/ ,int) ; 
 struct pci_devinfo* pci_fill_devinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 

struct pci_devinfo *
pci_read_device(device_t pcib, device_t bus, int d, int b, int s, int f)
{
#define	REG(n, w)	PCIB_READ_CONFIG(pcib, b, s, f, n, w)
	uint16_t vid, did;

	vid = REG(PCIR_VENDOR, 2);
	did = REG(PCIR_DEVICE, 2);
	if (vid != 0xffff)
		return (pci_fill_devinfo(pcib, bus, d, b, s, f, vid, did));

	return (NULL);
}