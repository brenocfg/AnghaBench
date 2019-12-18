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
struct image_args {char* endp; scalar_t__ envc; char* begin_envv; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

char *
exec_args_get_begin_envv(struct image_args *args)
{

	KASSERT(args->endp != NULL, ("endp not initialized"));

	if (args->envc > 0)
		return (args->begin_envv);
	return (args->endp);
}