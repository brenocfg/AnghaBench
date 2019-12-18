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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_ATTRS ; 
 int /*<<< orphan*/  EFI_GLOBAL_GUID ; 
 int efi_set_variable (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_bootvar(const char *name, uint8_t *data, size_t size)
{

	return efi_set_variable(EFI_GLOBAL_GUID, name, data, size,
	    COMMON_ATTRS);
}