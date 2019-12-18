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
typedef  scalar_t__ uint64_t ;
struct _qs {int dummy; } ;
struct _cfg {scalar_t__* d; } ;

/* Variables and functions */
 scalar_t__ U_PARSE_ERR ; 
 scalar_t__ parse_bw (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
const_bw_parse(struct _qs *q, struct _cfg *dst, int ac, char *av[])
{
	uint64_t bw;

	(void)q;
	if (strncmp(av[0], "const", 5) != 0 && ac > 1)
		return 2; /* unrecognised */
	if (ac > 2)
		return 1; /* error */
	bw = parse_bw(av[ac - 1]);
	if (bw == U_PARSE_ERR) {
		return (ac == 2) ? 1 /* error */ : 2 /* unrecognised */;
	}
	dst->d[0] = bw;
	return 0;	/* success */
}