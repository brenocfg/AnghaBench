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
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_rm (char*) ; 

__attribute__((used)) static void clar_unsandbox(void)
{
	if (_clar_path[0] == '\0')
		return;

	cl_must_pass(chdir(".."));

	fs_rm(_clar_path);
}