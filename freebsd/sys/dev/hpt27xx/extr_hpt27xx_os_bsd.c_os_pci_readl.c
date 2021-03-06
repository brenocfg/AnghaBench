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
struct TYPE_2__ {int /*<<< orphan*/  pcidev; } ;
typedef  TYPE_1__* PHBA ;
typedef  int /*<<< orphan*/  HPT_U8 ;
typedef  int /*<<< orphan*/  HPT_U32 ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

HPT_U32 os_pci_readl (void *osext, HPT_U8 offset)
{
    return  pci_read_config(((PHBA)osext)->pcidev, offset, 4);
}