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
struct mac {int dummy; } ;
struct image_args {scalar_t__ endp; int /*<<< orphan*/  envc; scalar_t__ begin_argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_ARGV (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AUDIT_ARG_ENVV (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int do_execve (struct thread*,struct image_args*,struct mac*) ; 
 scalar_t__ exec_args_get_begin_envv (struct image_args*) ; 

int
kern_execve(struct thread *td, struct image_args *args, struct mac *mac_p)
{

	AUDIT_ARG_ARGV(args->begin_argv, args->argc,
	    exec_args_get_begin_envv(args) - args->begin_argv);
	AUDIT_ARG_ENVV(exec_args_get_begin_envv(args), args->envc,
	    args->endp - exec_args_get_begin_envv(args));
	return (do_execve(td, args, mac_p));
}