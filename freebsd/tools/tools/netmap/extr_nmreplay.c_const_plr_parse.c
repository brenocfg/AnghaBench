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
struct _cfg {double* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  ED (char*,double) ; 
 double parse_gen (char*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
const_plr_parse(struct _qs *q, struct _cfg *dst, int ac, char *av[])
{
	double plr;
	int err;

	(void)q;
	if (strcmp(av[0], "plr") != 0 && ac > 1)
		return 2; /* unrecognised */
	if (ac > 2)
		return 1; /* error */
	// XXX to be completed
	plr = parse_gen(av[ac-1], NULL, &err);
	if (err || plr < 0 || plr > 1)
		return 1;
	dst->d[0] = plr * (1<<24); /* scale is 16m */
	if (plr != 0 && dst->d[0] == 0)
		ED("WWW warning,  rounding %le down to 0", plr);
	return 0;	/* success */
}