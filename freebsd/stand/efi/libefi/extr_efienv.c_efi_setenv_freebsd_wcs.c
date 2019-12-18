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
typedef  int /*<<< orphan*/  efi_char ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetVariable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 int /*<<< orphan*/  FreeBSDBootVarGUID ; 
 TYPE_1__* RS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int ucs2len (int /*<<< orphan*/ *) ; 
 scalar_t__ utf8_to_ucs2 (char const*,int /*<<< orphan*/ **,size_t*) ; 

EFI_STATUS
efi_setenv_freebsd_wcs(const char *varname, CHAR16 *valstr)
{
	CHAR16 *var = NULL;
	size_t len;
	EFI_STATUS rv;

	if (utf8_to_ucs2(varname, &var, &len) != 0)
		return (EFI_OUT_OF_RESOURCES);
	rv = RS->SetVariable(var, &FreeBSDBootVarGUID,
	    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
	    (ucs2len(valstr) + 1) * sizeof(efi_char), valstr);
	free(var);
	return (rv);
}