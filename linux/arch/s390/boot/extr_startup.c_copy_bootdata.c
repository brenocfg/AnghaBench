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
struct TYPE_2__ {scalar_t__ bootdata_size; scalar_t__ bootdata_preserved_size; scalar_t__ bootdata_preserved_off; scalar_t__ bootdata_off; } ;

/* Variables and functions */
 scalar_t__ __boot_data_end ; 
 scalar_t__ __boot_data_preserved_end ; 
 scalar_t__ __boot_data_preserved_start ; 
 scalar_t__ __boot_data_start ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 TYPE_1__ vmlinux ; 

__attribute__((used)) static void copy_bootdata(void)
{
	if (__boot_data_end - __boot_data_start != vmlinux.bootdata_size)
		error(".boot.data section size mismatch");
	memcpy((void *)vmlinux.bootdata_off, __boot_data_start, vmlinux.bootdata_size);
	if (__boot_data_preserved_end - __boot_data_preserved_start != vmlinux.bootdata_preserved_size)
		error(".boot.preserved.data section size mismatch");
	memcpy((void *)vmlinux.bootdata_preserved_off, __boot_data_preserved_start, vmlinux.bootdata_preserved_size);
}