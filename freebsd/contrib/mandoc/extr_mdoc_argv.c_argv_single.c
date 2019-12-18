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
struct roff_man {int dummy; } ;
struct mdoc_argv {int sz; char** value; } ;
typedef  enum margserr { ____Placeholder_margserr } margserr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGSFL_NONE ; 
 int ARGS_ALLOC ; 
 int ARGS_EOLN ; 
 int args (struct roff_man*,int,int*,char*,int /*<<< orphan*/ ,char**) ; 
 char** mandoc_malloc (int) ; 
 char* mandoc_strdup (char*) ; 

__attribute__((used)) static void
argv_single(struct roff_man *mdoc, int line,
		struct mdoc_argv *v, int *pos, char *buf)
{
	enum margserr	 ac;
	char		*p;

	ac = args(mdoc, line, pos, buf, ARGSFL_NONE, &p);
	if (ac == ARGS_EOLN)
		return;

	if (ac != ARGS_ALLOC)
		p = mandoc_strdup(p);

	v->sz = 1;
	v->value = mandoc_malloc(sizeof(char *));
	v->value[0] = p;
}