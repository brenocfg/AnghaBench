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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENOENT ; 
 int EWOULDBLOCK ; 
 int linker_search_symbol_name_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stack_symbol(vm_offset_t pc, char *namebuf, u_int buflen, long *offset,
    int flags)
{
	int error;

	error = linker_search_symbol_name_flags((caddr_t)pc, namebuf, buflen,
	    offset, flags);
	if (error == 0 || error == EWOULDBLOCK)
		return (error);

	*offset = 0;
	strlcpy(namebuf, "??", buflen);
	return (ENOENT);
}