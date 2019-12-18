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
typedef  int /*<<< orphan*/  EXCMDLIST ;
typedef  char CHAR_T ;

/* Variables and functions */
 size_t C_UNMAP ; 
 int const* cmds ; 
 int* ex_comm_search (char*,size_t) ; 

int
ex_is_unmap(CHAR_T *name, size_t len)
{
	EXCMDLIST const *cp;

	/*
	 * The command the vi input routines are really interested in
	 * is "unmap!", not just unmap.
	 */
	if (name[len - 1] != '!')
		return (0);
	--len;
	return ((cp = ex_comm_search(name, len)) != NULL &&
	    cp == &cmds[C_UNMAP]);
}