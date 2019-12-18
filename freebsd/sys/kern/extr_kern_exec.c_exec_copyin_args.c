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
typedef  scalar_t__ u_long ;
struct image_args {int dummy; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  bzero (struct image_args*,int) ; 
 int exec_alloc_args (struct image_args*) ; 
 int exec_args_add_arg (struct image_args*,char*,int /*<<< orphan*/ ) ; 
 int exec_args_add_env (struct image_args*,char*,int /*<<< orphan*/ ) ; 
 int exec_args_add_fname (struct image_args*,char const*,int) ; 
 int /*<<< orphan*/  exec_free_args (struct image_args*) ; 
 int fueword (int /*<<< orphan*/ ,scalar_t__*) ; 

int
exec_copyin_args(struct image_args *args, const char *fname,
    enum uio_seg segflg, char **argv, char **envv)
{
	u_long arg, env;
	int error;

	bzero(args, sizeof(*args));
	if (argv == NULL)
		return (EFAULT);

	/*
	 * Allocate demand-paged memory for the file name, argument, and
	 * environment strings.
	 */
	error = exec_alloc_args(args);
	if (error != 0)
		return (error);

	/*
	 * Copy the file name.
	 */
	error = exec_args_add_fname(args, fname, segflg);
	if (error != 0)
		goto err_exit;

	/*
	 * extract arguments first
	 */
	for (;;) {
		error = fueword(argv++, &arg);
		if (error == -1) {
			error = EFAULT;
			goto err_exit;
		}
		if (arg == 0)
			break;
		error = exec_args_add_arg(args, (char *)(uintptr_t)arg,
		    UIO_USERSPACE);
		if (error != 0)
			goto err_exit;
	}

	/*
	 * extract environment strings
	 */
	if (envv) {
		for (;;) {
			error = fueword(envv++, &env);
			if (error == -1) {
				error = EFAULT;
				goto err_exit;
			}
			if (env == 0)
				break;
			error = exec_args_add_env(args,
			    (char *)(uintptr_t)env, UIO_USERSPACE);
			if (error != 0)
				goto err_exit;
		}
	}

	return (0);

err_exit:
	exec_free_args(args);
	return (error);
}