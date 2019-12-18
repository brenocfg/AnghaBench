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
struct image_args {scalar_t__ envc; int /*<<< orphan*/  argc; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int exec_args_add_str (struct image_args*,char const*,int,int /*<<< orphan*/ *) ; 

int
exec_args_add_arg(struct image_args *args, const char *argp,
    enum uio_seg segflg)
{

	KASSERT(args->envc == 0, ("appending args after env"));

	return (exec_args_add_str(args, argp, segflg, &args->argc));
}