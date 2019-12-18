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
typedef  int /*<<< orphan*/  HPT_U8 ;
typedef  int /*<<< orphan*/  HPT_U32 ;

/* Variables and functions */
 int /*<<< orphan*/  pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

HPT_U32 pcicfg_read_dword(HPT_U8 bus, HPT_U8 dev, HPT_U8 func, HPT_U8 reg)
{
	return (HPT_U32)pci_cfgregread(bus, dev, func, reg, 4);;
}