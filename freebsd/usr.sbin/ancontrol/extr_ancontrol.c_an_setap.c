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
struct ether_addr {int dummy; } ;
struct an_req {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_ltv_aplist {int /*<<< orphan*/  an_ap4; int /*<<< orphan*/  an_ap3; int /*<<< orphan*/  an_ap2; int /*<<< orphan*/  an_ap1; } ;
typedef  int /*<<< orphan*/  areq ;

/* Variables and functions */
#define  ACT_SET_AP1 131 
#define  ACT_SET_AP2 130 
#define  ACT_SET_AP3 129 
#define  ACT_SET_AP4 128 
 int /*<<< orphan*/  AN_RID_APLIST ; 
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  an_setval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  bcopy (struct ether_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct ether_addr* ether_aton (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
an_setap(const char *iface, int act, void *arg)
{
	struct an_ltv_aplist	*ap;
	struct an_req		areq;
	struct ether_addr	*addr;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_APLIST;

	an_getval(iface, &areq);
	ap = (struct an_ltv_aplist *)&areq;

	addr = ether_aton((char *)arg);

	if (addr == NULL)
		errx(1, "badly formatted address");

	switch(act) {
	case ACT_SET_AP1:
		bzero(ap->an_ap1, ETHER_ADDR_LEN);
		bcopy(addr, &ap->an_ap1, ETHER_ADDR_LEN);
		break;
	case ACT_SET_AP2:
		bzero(ap->an_ap2, ETHER_ADDR_LEN);
		bcopy(addr, &ap->an_ap2, ETHER_ADDR_LEN);
		break;
	case ACT_SET_AP3:
		bzero(ap->an_ap3, ETHER_ADDR_LEN);
		bcopy(addr, &ap->an_ap3, ETHER_ADDR_LEN);
		break;
	case ACT_SET_AP4:
		bzero(ap->an_ap4, ETHER_ADDR_LEN);
		bcopy(addr, &ap->an_ap4, ETHER_ADDR_LEN);
		break;
	default:
		errx(1, "unknown action");
		break;
	}

	an_setval(iface, &areq);
	exit(0);
}