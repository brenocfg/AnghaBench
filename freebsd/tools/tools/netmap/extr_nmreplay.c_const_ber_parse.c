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
typedef  int uint32_t ;
struct _qs {int dummy; } ;
struct _cfg {int arg_len; int* arg; double* d; } ;
typedef  int /*<<< orphan*/  _P64 ;

/* Variables and functions */
 int MAX_PKT ; 
 int /*<<< orphan*/  RD (int,char*,int,double,int /*<<< orphan*/ ) ; 
 int* calloc (int,int) ; 
 double parse_gen (char*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
const_ber_parse(struct _qs *q, struct _cfg *dst, int ac, char *av[])
{
	double ber, ber8, cur;
	int i, err;
	uint32_t *plr;
	const uint32_t mask = (1<<24) - 1;

	(void)q;
	if (strcmp(av[0], "ber") != 0)
		return 2; /* unrecognised */
	if (ac != 2)
		return 1; /* error */
	ber = parse_gen(av[ac-1], NULL, &err);
	if (err || ber < 0 || ber > 1)
		return 1;
	dst->arg_len = MAX_PKT * sizeof(uint32_t);
	plr = calloc(1, dst->arg_len);
	if (plr == NULL)
		return 1; /* no memory */
	dst->arg = plr;
	ber8 = 1 - ber;
	ber8 *= ber8; /* **2 */
	ber8 *= ber8; /* **4 */
	ber8 *= ber8; /* **8 */
	cur = 1;
	for (i=0; i < MAX_PKT; i++, cur *= ber8) {
		plr[i] = (mask + 1)*(1 - cur);
		if (plr[i] > mask)
			plr[i] = mask;
#if 0
		if (i>= 60) //  && plr[i] < mask/2)
			RD(50,"%4d: %le %ld", i, 1.0 - cur, (_P64)plr[i]);
#endif
	}
	dst->d[0] = ber * (mask + 1);
	return 0;	/* success */
}