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
struct _qs {int dummy; } ;
struct _cfg {int (* parse ) (struct _qs*,struct _cfg*,int,char**) ;char* optarg; int /*<<< orphan*/  d; scalar_t__ arg_len; int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED (char*,...) ; 
 int /*<<< orphan*/  ND (char*,char*,char const*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char**) ; 
 char** split_arg (char const*,int*) ; 
 int stub1 (struct _qs*,struct _cfg*,int,char**) ; 

__attribute__((used)) static int
cmd_apply(const struct _cfg *a, const char *arg, struct _qs *q, struct _cfg *dst)
{
	int ac = 0;
	char **av;
	int i;

	if (arg == NULL || *arg == '\0')
		return 1; /* no argument may be ok */
	if (a == NULL || dst == NULL) {
		ED("program error - invalid arguments");
		exit(1);
	}
	av = split_arg(arg, &ac);
	if (av == NULL)
		return 1; /* error */
	for (i = 0; a[i].parse; i++) {
		struct _cfg x = a[i];
		const char *errmsg = x.optarg;
		int ret;

		x.arg = NULL;
		x.arg_len = 0;
		bzero(&x.d, sizeof(x.d));
		ND("apply %s to %s", av[0], errmsg);
		ret = x.parse(q, &x, ac, av);
		if (ret == 2) /* not recognised */
			continue;
		if (ret == 1) {
			ED("invalid arguments: need '%s' have '%s'",
				errmsg, arg);
			break;
		}
		x.optarg = arg;
		*dst = x;
		return 0;
	}
	ED("arguments %s not recognised", arg);
	free(av);
	return 1;
}