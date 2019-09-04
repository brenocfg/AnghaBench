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
 char* _clar_path ; 
 scalar_t__ build_sandbox_path () ; 
 scalar_t__ chdir (char*) ; 

__attribute__((used)) static int clar_sandbox(void)
{
	if (_clar_path[0] == '\0' && build_sandbox_path() < 0)
		return -1;

	if (chdir(_clar_path) != 0)
		return -1;

	return 0;
}