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
typedef  int /*<<< orphan*/  u64 ;
struct uv_systab {int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  enum uv_bios_cmd { ____Placeholder_uv_bios_cmd } uv_bios_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_STATUS_UNIMPLEMENTED ; 
 int /*<<< orphan*/  EFI_OLD_MEMMAP ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efi_call (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efi_call_virt_pointer (struct uv_systab*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efi_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  function ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct uv_systab* uv_systab ; 

__attribute__((used)) static s64 __uv_bios_call(enum uv_bios_cmd which, u64 a1, u64 a2, u64 a3,
			u64 a4, u64 a5)
{
	struct uv_systab *tab = uv_systab;
	s64 ret;

	if (!tab || !tab->function)
		/*
		 * BIOS does not support UV systab
		 */
		return BIOS_STATUS_UNIMPLEMENTED;

	/*
	 * If EFI_OLD_MEMMAP is set, we need to fall back to using our old EFI
	 * callback method, which uses efi_call() directly, with the kernel page tables:
	 */
	if (unlikely(efi_enabled(EFI_OLD_MEMMAP)))
		ret = efi_call((void *)__va(tab->function), (u64)which, a1, a2, a3, a4, a5);
	else
		ret = efi_call_virt_pointer(tab, function, (u64)which, a1, a2, a3, a4, a5);

	return ret;
}