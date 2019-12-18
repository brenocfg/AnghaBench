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
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GlobalBootVarGUID ; 
 int /*<<< orphan*/  efi_getenv (int /*<<< orphan*/ *,char const*,void*,size_t*) ; 

EFI_STATUS
efi_global_getenv(const char *v, void *data, size_t *len)
{

	return (efi_getenv(&GlobalBootVarGUID, v, data, len));
}