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
struct efirt_callinfo {char* ec_name; int /*<<< orphan*/  ec_efi_status; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int efi_enter () ; 
 int /*<<< orphan*/  efi_leave () ; 
 int efi_rt_arch_call (struct efirt_callinfo*) ; 
 int efi_rt_arch_call_nofault (struct efirt_callinfo*) ; 
 scalar_t__ efi_rt_handle_faults ; 
 int efi_status_to_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 

__attribute__((used)) static int
efi_call(struct efirt_callinfo *ecp)
{
	int error;

	error = efi_enter();
	if (error != 0)
		return (error);
	error = efi_rt_handle_faults ? efi_rt_arch_call(ecp) :
	    efi_rt_arch_call_nofault(ecp);
	efi_leave();
	if (error == 0)
		error = efi_status_to_errno(ecp->ec_efi_status);
	else if (bootverbose)
		printf("EFI %s call faulted, error %d\n", ecp->ec_name, error);
	return (error);
}