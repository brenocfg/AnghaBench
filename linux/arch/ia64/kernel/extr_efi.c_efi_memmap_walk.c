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
typedef  int /*<<< orphan*/  efi_freemem_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_MEMORY_WB ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
efi_memmap_walk (efi_freemem_callback_t callback, void *arg)
{
	walk(callback, arg, EFI_MEMORY_WB);
}