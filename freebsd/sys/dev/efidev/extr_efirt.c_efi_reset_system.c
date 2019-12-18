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
struct efirt_callinfo {char* ec_name; int ec_argcnt; uintptr_t ec_arg1; uintptr_t ec_arg2; uintptr_t ec_arg3; uintptr_t ec_arg4; int /*<<< orphan*/  ec_fptr; } ;
typedef  enum efi_reset { ____Placeholder_efi_reset } efi_reset ;
typedef  int /*<<< orphan*/  ec ;

/* Variables and functions */
#define  EFI_RESET_COLD 130 
#define  EFI_RESET_SHUTDOWN 129 
#define  EFI_RESET_WARM 128 
 int /*<<< orphan*/  EFI_RT_METHOD_PA (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  bzero (struct efirt_callinfo*,int) ; 
 int efi_call (struct efirt_callinfo*) ; 
 int /*<<< orphan*/ * efi_runtime ; 
 int /*<<< orphan*/  rt_reset ; 

int
efi_reset_system(enum efi_reset type)
{
	struct efirt_callinfo ec;

	switch (type) {
	case EFI_RESET_COLD:
	case EFI_RESET_WARM:
	case EFI_RESET_SHUTDOWN:
		break;
	default:
		return (EINVAL);
	}
	if (efi_runtime == NULL)
		return (ENXIO);
	bzero(&ec, sizeof(ec));
	ec.ec_name = "rt_reset";
	ec.ec_argcnt = 4;
	ec.ec_arg1 = (uintptr_t)type;
	ec.ec_arg2 = (uintptr_t)0;
	ec.ec_arg3 = (uintptr_t)0;
	ec.ec_arg4 = (uintptr_t)NULL;
	ec.ec_fptr = EFI_RT_METHOD_PA(rt_reset);
	return (efi_call(&ec));
}