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
struct image_args {size_t stringspace; int /*<<< orphan*/ * endp; int /*<<< orphan*/ * begin_argv; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int E2BIG ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int UIO_SYSSPACE ; 
 int copyinstr (char const*,int /*<<< orphan*/ *,size_t,size_t*) ; 
 int copystr (char const*,int /*<<< orphan*/ *,size_t,size_t*) ; 

__attribute__((used)) static int
exec_args_add_str(struct image_args *args, const char *str,
    enum uio_seg segflg, int *countp)
{
	int error;
	size_t length;

	KASSERT(args->endp != NULL, ("endp not initialized"));
	KASSERT(args->begin_argv != NULL, ("begin_argp not initialized"));

	error = (segflg == UIO_SYSSPACE) ?
	    copystr(str, args->endp, args->stringspace, &length) :
	    copyinstr(str, args->endp, args->stringspace, &length);
	if (error != 0)
		return (error == ENAMETOOLONG ? E2BIG : error);
	args->stringspace -= length;
	args->endp += length;
	(*countp)++;

	return (0);
}