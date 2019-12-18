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
 int PATH_MAX ; 
 int bind_test (char*) ; 
 int connect_test (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 int /*<<< orphan*/  push_path (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  unwind () ; 

int
main(void)
{
	char directory_path[PATH_MAX];
	int error;

	strlcpy(directory_path, "/tmp/unix_bind.XXXXXXX", PATH_MAX);
	if (mkdtemp(directory_path) == NULL)
		err(-1, "mkdtemp");
	push_path(directory_path);

	error = bind_test(directory_path);

	if (error == 0)
		error = connect_test(directory_path);

	unwind();
	return (error);
}