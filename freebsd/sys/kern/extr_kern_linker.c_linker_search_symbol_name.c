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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int linker_search_symbol_name_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long*,int /*<<< orphan*/ ) ; 

int
linker_search_symbol_name(caddr_t value, char *buf, u_int buflen,
    long *offset)
{

	return (linker_search_symbol_name_flags(value, buf, buflen, offset,
	    M_WAITOK));
}