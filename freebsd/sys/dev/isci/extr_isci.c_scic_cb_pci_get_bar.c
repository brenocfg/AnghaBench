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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  SCI_CONTROLLER_HANDLE_T ;
typedef  scalar_t__ POINTER_UINT ;

/* Variables and functions */

void *
scic_cb_pci_get_bar(SCI_CONTROLLER_HANDLE_T controller,
    uint16_t bar_number)
{

	return ((void *)(POINTER_UINT)((uint32_t)bar_number << 28));
}