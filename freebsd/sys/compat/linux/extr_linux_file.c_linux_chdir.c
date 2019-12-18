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
struct thread {int dummy; } ;
struct linux_chdir_args {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCONVPATHEXIST (struct thread*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int kern_chdir (struct thread*,char*,int /*<<< orphan*/ ) ; 

int
linux_chdir(struct thread *td, struct linux_chdir_args *args)
{
	char *path;
	int error;

	LCONVPATHEXIST(td, args->path, &path);

	error = kern_chdir(td, path, UIO_SYSSPACE);
	LFREEPATH(path);
	return (error);
}