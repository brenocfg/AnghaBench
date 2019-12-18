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
 int* _prom_argc ; 
 char** _prom_argv ; 
 char** _prom_envp ; 
 scalar_t__ fw_arg0 ; 
 scalar_t__ fw_arg1 ; 
 scalar_t__ fw_arg2 ; 

int generic_prom_present(void)
{
	_prom_argc = (int *)fw_arg0;
	_prom_argv = (char **)fw_arg1;
	_prom_envp = (char **)fw_arg2;

	return 1;
}