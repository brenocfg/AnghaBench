#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SONYPI_G10A ; 
 int /*<<< orphan*/  SONYPI_IRQ_PORT ; 
 int SONYPI_IRQ_SHIFT ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ sonypi_device ; 

__attribute__((used)) static void sonypi_type1_dis(void)
{
	u32 v;

	pci_read_config_dword(sonypi_device.dev, SONYPI_G10A, &v);
	v = v & 0xFF3FFFFF;
	pci_write_config_dword(sonypi_device.dev, SONYPI_G10A, v);

	v = inl(SONYPI_IRQ_PORT);
	v |= (0x3 << SONYPI_IRQ_SHIFT);
	outl(v, SONYPI_IRQ_PORT);
}