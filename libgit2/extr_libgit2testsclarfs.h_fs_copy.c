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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  shell_out (char**) ; 
 char* strdup (char const*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
fs_copy(const char *_source, const char *dest)
{
	char *argv[5];
	char *source;
	size_t source_len;

	source = strdup(_source);
	source_len = strlen(source);

	if (source[source_len - 1] == '/')
		source[source_len - 1] = 0;

	argv[0] = "/bin/cp";
	argv[1] = "-R";
	argv[2] = source;
	argv[3] = (char *)dest;
	argv[4] = NULL;

	cl_must_pass_(
		shell_out(argv),
		"Failed to copy test fixtures to sandbox"
	);

	free(source);
}