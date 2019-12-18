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
typedef  int uint64_t ;
struct _qs {int dummy; } ;
struct _cfg {int arg_len; int /*<<< orphan*/ * arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (int,char*,int,double) ; 
 int PTS_D_EXP ; 
 int U_PARSE_ERR ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int log2 (double) ; 
 int parse_time (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
exp_delay_parse(struct _qs *q, struct _cfg *dst, int ac, char *av[])
{
#define	PTS_D_EXP	512
	uint64_t i, d_av, d_min, *t; /*table of values */

        (void)q;
        if (strcmp(av[0], "exp") != 0)
		return 2; /* not recognised */
        if (ac != 3)
                return 1; /* error */
        d_av = parse_time(av[1]);
        d_min = parse_time(av[2]);
        if (d_av == U_PARSE_ERR || d_min == U_PARSE_ERR || d_av < d_min)
                return 1; /* error */
	d_av -= d_min;
	dst->arg_len = PTS_D_EXP * sizeof(uint64_t);
	dst->arg = calloc(1, dst->arg_len);
	if (dst->arg == NULL)
		return 1; /* no memory */
	t = (uint64_t *)dst->arg;
	/* tabulate -ln(1-n)*delay  for n in 0..1 */
	for (i = 0; i < PTS_D_EXP; i++) {
		double d = -log2 ((double)(PTS_D_EXP - i) / PTS_D_EXP) * d_av + d_min;
		t[i] = (uint64_t)d;
		ND(5, "%ld: %le", i, d);
	}
        return 0;
}