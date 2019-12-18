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
struct s_appends {int dummy; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */
 int appendnum ; 
 int /*<<< orphan*/ * appends ; 
 int /*<<< orphan*/ ** compile_stream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fixuplabel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/ * match ; 
 int maxnsub ; 
 int /*<<< orphan*/  prog ; 
 int /*<<< orphan*/  uselabel () ; 

void
compile(void)
{
	*compile_stream(&prog) = NULL;
	fixuplabel(prog, NULL);
	uselabel();
	if (appendnum == 0)
		appends = NULL;
	else if ((appends = malloc(sizeof(struct s_appends) * appendnum)) ==
	    NULL)
		err(1, "malloc");
	if ((match = malloc((maxnsub + 1) * sizeof(regmatch_t))) == NULL)
		err(1, "malloc");
}