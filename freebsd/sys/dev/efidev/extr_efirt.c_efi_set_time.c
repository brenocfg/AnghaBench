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
struct efi_tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_TIME_LOCK () ; 
 int /*<<< orphan*/  EFI_TIME_UNLOCK () ; 
 int ENXIO ; 
 int /*<<< orphan*/ * efi_runtime ; 
 int efi_set_time_locked (struct efi_tm*) ; 

int
efi_set_time(struct efi_tm *tm)
{
	int error;

	if (efi_runtime == NULL)
		return (ENXIO);
	EFI_TIME_LOCK();
	error = efi_set_time_locked(tm);
	EFI_TIME_UNLOCK();
	return (error);
}