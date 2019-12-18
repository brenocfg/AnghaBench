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
 int MULTI_STEP ; 
 int args (struct roff_man*,int,int*,char*,int /*<<< orphan*/ ,char**) ; 
 char** mandoc_reallocarray (char**,int,int) ; 
 char* mandoc_strdup (char*) ; 

__attribute__((used)) static void
argv_multi(struct roff_man *mdoc, int line,
		struct mdoc_argv *v, int *pos, char *buf)
{
	enum margserr	 ac;
	char		*p;

	for (v->sz = 0; ; v->sz++) {
		if (buf[*pos] == '-')
			break;
		ac = args(mdoc, line, pos, buf, ARGSFL_NONE, &p);
		if (ac == ARGS_EOLN)
			break;

		if (v->sz % MULTI_STEP == 0)
			v->value = mandoc_reallocarray(v->value,
			    v->sz + MULTI_STEP, sizeof(char *));

		if (ac != ARGS_ALLOC)
			p = mandoc_strdup(p);
		v->value[(int)v->sz] = p;
	}
}