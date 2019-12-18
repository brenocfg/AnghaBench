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
typedef  size_t u_int ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getuid () ; 
 char* tilde_expand_filename (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tilde_expand_paths(char **paths, u_int num_paths)
{
	u_int i;
	char *cp;

	for (i = 0; i < num_paths; i++) {
		cp = tilde_expand_filename(paths[i], getuid());
		free(paths[i]);
		paths[i] = cp;
	}
}