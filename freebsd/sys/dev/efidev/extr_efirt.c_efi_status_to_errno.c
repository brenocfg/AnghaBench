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
typedef  size_t u_long ;
typedef  int efi_status ;

/* Variables and functions */
 int EDOOFUS ; 
 int* efi_status2err ; 
 size_t nitems (int*) ; 

__attribute__((used)) static int
efi_status_to_errno(efi_status status)
{
	u_long code;

	code = status & 0x3ffffffffffffffful;
	return (code < nitems(efi_status2err) ? efi_status2err[code] : EDOOFUS);
}