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
struct image_args {scalar_t__ envc; int /*<<< orphan*/  endp; int /*<<< orphan*/  begin_envv; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int exec_args_add_str (struct image_args*,char const*,int,scalar_t__*) ; 

int
exec_args_add_env(struct image_args *args, const char *envp,
    enum uio_seg segflg)
{

	if (args->envc == 0)
		args->begin_envv = args->endp;

	return (exec_args_add_str(args, envp, segflg, &args->envc));
}