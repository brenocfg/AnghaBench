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
struct efirt_callinfo {char* ec_name; int ec_argcnt; uintptr_t ec_arg1; uintptr_t ec_arg2; int /*<<< orphan*/  ec_fptr; } ;
struct efi_tmcap {int dummy; } ;
struct efi_tm {int dummy; } ;
typedef  int /*<<< orphan*/  ec ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_RT_METHOD_PA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_TIME_OWNED () ; 
 int ENXIO ; 
 int /*<<< orphan*/  bzero (struct efirt_callinfo*,int) ; 
 int efi_call (struct efirt_callinfo*) ; 
 int /*<<< orphan*/ * efi_runtime ; 
 int /*<<< orphan*/  rt_gettime ; 

__attribute__((used)) static int
efi_get_time_locked(struct efi_tm *tm, struct efi_tmcap *tmcap)
{
	struct efirt_callinfo ec;

	EFI_TIME_OWNED();
	if (efi_runtime == NULL)
		return (ENXIO);
	bzero(&ec, sizeof(ec));
	ec.ec_name = "rt_gettime";
	ec.ec_argcnt = 2;
	ec.ec_arg1 = (uintptr_t)tm;
	ec.ec_arg2 = (uintptr_t)tmcap;
	ec.ec_fptr = EFI_RT_METHOD_PA(rt_gettime);
	return (efi_call(&ec));
}