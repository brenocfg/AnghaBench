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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_2__ {void* addr; char* symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int isc__backtrace_nsymbols ; 
 TYPE_1__* isc__backtrace_symtable ; 

isc_result_t
isc_backtrace_getsymbolfromindex(int idx, const void **addrp,
				 const char **symbolp)
{
	REQUIRE(addrp != NULL && *addrp == NULL);
	REQUIRE(symbolp != NULL && *symbolp == NULL);

	if (idx < 0 || idx >= isc__backtrace_nsymbols)
		return (ISC_R_RANGE);

	*addrp = isc__backtrace_symtable[idx].addr;
	*symbolp = isc__backtrace_symtable[idx].symbol;
	return (ISC_R_SUCCESS);
}