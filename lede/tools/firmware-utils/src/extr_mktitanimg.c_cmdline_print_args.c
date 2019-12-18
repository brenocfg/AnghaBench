#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t index; struct TYPE_5__* p_next; } ;
struct TYPE_4__ {int optc; int argc; TYPE_2__* list; } ;
typedef  TYPE_1__ CMDLINE_ARGS ;
typedef  TYPE_2__ CMDLINE_ARG ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void cmdline_print_args(CMDLINE_ARGS* p_arglist, char* argv[])
{
	CMDLINE_ARG*	p_arg;

	printf("   Number of times option was specified: %d\n", p_arglist->optc);
	printf("   Number of Arguments:                  %d\n", p_arglist->argc);

	if(p_arglist->argc > 0)
	{
		printf("   Argument List: ");

		for(p_arg=p_arglist->list; p_arg != NULL; p_arg=p_arg->p_next)
			printf("%s ", argv[p_arg->index]);
	}

	printf("\n");
}