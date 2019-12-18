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
 char* HARDLIM_WARN ; 
 int auditwarnlog (char**) ; 

int
audit_warn_hard(char *filename)
{
	char *args[3];

	args[0] = HARDLIM_WARN;
	args[1] = filename;
	args[2] = NULL;

	return (auditwarnlog(args));
}