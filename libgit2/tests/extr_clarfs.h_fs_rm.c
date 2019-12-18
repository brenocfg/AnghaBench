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
 int /*<<< orphan*/  cl_must_pass_ (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shell_out (char**) ; 

__attribute__((used)) static void
fs_rm(const char *source)
{
	char *argv[4];

	argv[0] = "/bin/rm";
	argv[1] = "-Rf";
	argv[2] = (char *)source;
	argv[3] = NULL;

	cl_must_pass_(
		shell_out(argv),
		"Failed to cleanup the sandbox"
	);
}