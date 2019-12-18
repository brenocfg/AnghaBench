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
typedef  int /*<<< orphan*/  u32 ;
struct efivar_operations {int /*<<< orphan*/  (* query_variable_store ) (int /*<<< orphan*/ ,unsigned long,int) ;} ;
typedef  int /*<<< orphan*/  efi_status_t ;
struct TYPE_2__ {struct efivar_operations* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_UNSUPPORTED ; 
 TYPE_1__* __efivars ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static efi_status_t
check_var_size_nonblocking(u32 attributes, unsigned long size)
{
	const struct efivar_operations *fops;

	if (!__efivars)
		return EFI_UNSUPPORTED;

	fops = __efivars->ops;

	if (!fops->query_variable_store)
		return EFI_UNSUPPORTED;

	return fops->query_variable_store(attributes, size, true);
}