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
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int cl_toggle_filemode (char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

bool cl_is_chmod_supported(void)
{
	static int _is_supported = -1;

	if (_is_supported < 0) {
		cl_git_mkfile("filemode.t", "Test if filemode can be modified");
		_is_supported = cl_toggle_filemode("filemode.t");
		cl_must_pass(p_unlink("filemode.t"));
	}

	return _is_supported;
}