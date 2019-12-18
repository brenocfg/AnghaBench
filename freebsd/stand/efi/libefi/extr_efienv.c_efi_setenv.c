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
typedef  int /*<<< orphan*/  __size_t ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetVariable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_OUT_OF_RESOURCES ; 
 TYPE_1__* RS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ utf8_to_ucs2 (char const*,int /*<<< orphan*/ **,size_t*) ; 

EFI_STATUS
efi_setenv(EFI_GUID *guid, const char *varname, UINT32 attr, void *data, __size_t len)
{
	EFI_STATUS rv;
	CHAR16 *uv;
	size_t ul;

	uv = NULL;
	if (utf8_to_ucs2(varname, &uv, &ul) != 0)
		return (EFI_OUT_OF_RESOURCES);

	rv = RS->SetVariable(uv, guid, attr, len, data);
	free(uv);
	return (rv);
}