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
struct TYPE_2__ {int /*<<< orphan*/  (* SetVariable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 TYPE_1__* RS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ utf8_to_ucs2 (char const*,int /*<<< orphan*/ **,size_t*) ; 

EFI_STATUS
efi_delenv(EFI_GUID *guid, const char *name)
{
	CHAR16 *var;
	size_t len;
	EFI_STATUS rv;

	var = NULL;
	if (utf8_to_ucs2(name, &var, &len) != 0)
		return (EFI_OUT_OF_RESOURCES);

	rv = RS->SetVariable(var, guid, 0, 0, NULL);
	free(var);
	return (rv);
}