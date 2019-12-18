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
typedef  size_t UINTN ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_2__ {scalar_t__ (* GetVariable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,void*) ;} ;
typedef  scalar_t__ EFI_STATUS ;
typedef  int /*<<< orphan*/  EFI_GUID ;
typedef  int /*<<< orphan*/  CHAR16 ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 scalar_t__ EFI_OUT_OF_RESOURCES ; 
 scalar_t__ EFI_SUCCESS ; 
 TYPE_1__* RS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,void*) ; 
 scalar_t__ utf8_to_ucs2 (char const*,int /*<<< orphan*/ **,size_t*) ; 

EFI_STATUS
efi_getenv(EFI_GUID *g, const char *v, void *data, size_t *len)
{
	size_t ul;
	CHAR16 *uv;
	UINT32 attr;
	UINTN dl;
	EFI_STATUS rv;

	uv = NULL;
	if (utf8_to_ucs2(v, &uv, &ul) != 0)
		return (EFI_OUT_OF_RESOURCES);
	dl = *len;
	rv = RS->GetVariable(uv, g, &attr, &dl, data);
	if (rv == EFI_SUCCESS || rv == EFI_BUFFER_TOO_SMALL)
		*len = dl;
	free(uv);
	return (rv);
}