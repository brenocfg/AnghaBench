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

/* Variables and functions */
 int sq_dequote_to_argv_internal (char*,char const***,int*,int*,int /*<<< orphan*/ *) ; 

int sq_dequote_to_argv(char *arg, const char ***argv, int *nr, int *alloc)
{
	return sq_dequote_to_argv_internal(arg, argv, nr, alloc, NULL);
}