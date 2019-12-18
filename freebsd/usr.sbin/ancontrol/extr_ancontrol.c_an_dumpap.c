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
struct an_req {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_ltv_aplist {int /*<<< orphan*/  an_ap4; int /*<<< orphan*/  an_ap3; int /*<<< orphan*/  an_ap2; int /*<<< orphan*/  an_ap1; } ;
typedef  int /*<<< orphan*/  areq ;

/* Variables and functions */
 int /*<<< orphan*/  AN_RID_APLIST ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  an_printhex (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
an_dumpap(const char *iface)
{
	struct an_ltv_aplist	*ap;
	struct an_req		areq;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_APLIST;

	an_getval(iface, &areq);

	ap = (struct an_ltv_aplist *)&areq;
	printf("Access point 1:\t\t\t");
	an_printhex((char *)&ap->an_ap1, ETHER_ADDR_LEN);
	printf("\nAccess point 2:\t\t\t");
	an_printhex((char *)&ap->an_ap2, ETHER_ADDR_LEN);
	printf("\nAccess point 3:\t\t\t");
	an_printhex((char *)&ap->an_ap3, ETHER_ADDR_LEN);
	printf("\nAccess point 4:\t\t\t");
	an_printhex((char *)&ap->an_ap4, ETHER_ADDR_LEN);
	printf("\n");

	return;
}