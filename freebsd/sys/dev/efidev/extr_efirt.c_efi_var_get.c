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
typedef  int /*<<< orphan*/  uint32_t ;
struct uuid {int dummy; } ;
struct efirt_callinfo {int ec_argcnt; char* ec_name; uintptr_t ec_arg1; uintptr_t ec_arg2; uintptr_t ec_arg3; uintptr_t ec_arg4; uintptr_t ec_arg5; int /*<<< orphan*/  ec_fptr; } ;
typedef  int /*<<< orphan*/  efi_char ;
typedef  int /*<<< orphan*/  ec ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_RT_METHOD_PA (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  bzero (struct efirt_callinfo*,int) ; 
 int efi_call (struct efirt_callinfo*) ; 
 int /*<<< orphan*/ * efi_runtime ; 
 int /*<<< orphan*/  rt_getvar ; 

int
efi_var_get(efi_char *name, struct uuid *vendor, uint32_t *attrib,
    size_t *datasize, void *data)
{
	struct efirt_callinfo ec;

	if (efi_runtime == NULL)
		return (ENXIO);
	bzero(&ec, sizeof(ec));
	ec.ec_argcnt = 5;
	ec.ec_name = "rt_getvar";
	ec.ec_arg1 = (uintptr_t)name;
	ec.ec_arg2 = (uintptr_t)vendor;
	ec.ec_arg3 = (uintptr_t)attrib;
	ec.ec_arg4 = (uintptr_t)datasize;
	ec.ec_arg5 = (uintptr_t)data;
	ec.ec_fptr = EFI_RT_METHOD_PA(rt_getvar);
	return (efi_call(&ec));
}