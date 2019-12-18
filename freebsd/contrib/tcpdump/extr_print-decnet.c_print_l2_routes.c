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
typedef  int u_int ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_LE_16BITS (char const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (char const,int) ; 
 int /*<<< orphan*/  RI_COST (int) ; 
 int /*<<< orphan*/  RI_HOPS (int) ; 

__attribute__((used)) static int
print_l2_routes(netdissect_options *ndo,
                const char *rp, u_int len)
{
	int count;
	int area;
	int info;

	/* The last short is a checksum */
	while (len > (3 * sizeof(short))) {
	    ND_TCHECK2(*rp, 3 * sizeof(short));
	    count = EXTRACT_LE_16BITS(rp);
	    if (count > 1024)
		return (1);	/* seems to be bogus from here on */
	    rp += sizeof(short);
	    len -= sizeof(short);
	    area = EXTRACT_LE_16BITS(rp);
	    rp += sizeof(short);
	    len -= sizeof(short);
	    info = EXTRACT_LE_16BITS(rp);
	    rp += sizeof(short);
	    len -= sizeof(short);
	    ND_PRINT((ndo, "{areas %d-%d cost %d hops %d} ", area, area + count,
			    RI_COST(info), RI_HOPS(info)));
	}
	return (1);

trunc:
	return (0);
}