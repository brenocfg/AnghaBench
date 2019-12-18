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
struct s_fixedpt {int /*<<< orphan*/  fraction; int /*<<< orphan*/  int_part; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
p_sfix(netdissect_options *ndo,
       register const struct s_fixedpt *sfp)
{
	register int i;
	register int f;
	register double ff;

	i = EXTRACT_16BITS(&sfp->int_part);
	f = EXTRACT_16BITS(&sfp->fraction);
	ff = f / 65536.0;		/* shift radix point by 16 bits */
	f = (int)(ff * 1000000.0);	/* Treat fraction as parts per million */
	ND_PRINT((ndo, "%d.%06d", i, f));
}