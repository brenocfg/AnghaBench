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
 char const** sys_errlist ; 
 int sys_nerr ; 

const char *
rtld_strerror(int errnum)
{

	if (errnum < 0 || errnum >= sys_nerr)
		return ("Unknown error");
	return (sys_errlist[errnum]);
}