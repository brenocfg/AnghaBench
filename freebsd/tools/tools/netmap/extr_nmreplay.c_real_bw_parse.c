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
struct _cfg {double* f; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED (char*,double) ; 
 double parse_gen (char*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
real_bw_parse(struct _qs *q, struct _cfg *dst, int ac, char *av[])
{
	double scale;

	(void)q;
	if (strcmp(av[0], "real") != 0)
		return 2; /* unrecognised */
	if (ac > 2) { /* second argument is optional */
		return 1; /* error */
	} else if (ac == 1) {
		scale = 1;
	} else {
		int err = 0;
		scale = parse_gen(av[ac-1], NULL, &err);
		if (err || scale <= 0 || scale > 1000)
			return 1;
	}
	ED("real -> scale is %.6f", scale);
	dst->f[0] = scale;
	return 0;	/* success */
}