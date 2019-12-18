#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct an_req {int an_len; int /*<<< orphan*/  an_type; } ;
struct an_ltv_ssidlist_new {TYPE_1__* an_entry; } ;
struct an_ltv_ssid_entry {int dummy; } ;
typedef  int /*<<< orphan*/  areq ;
struct TYPE_2__ {char* an_len; int /*<<< orphan*/  an_ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_RID_SSIDLIST ; 
 int MAX_SSIDS ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
an_dumpssid(const char *iface)
{
	struct an_ltv_ssidlist_new	*ssid;
	struct an_req		areq;
	int			i, max;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_SSIDLIST;

	an_getval(iface, &areq);

	max = (areq.an_len - 4) / sizeof(struct an_ltv_ssid_entry);
	if ( max > MAX_SSIDS ) {
		printf("Too many SSIDs only printing %d of %d\n",
		    MAX_SSIDS, max);
		max = MAX_SSIDS;
	}
	ssid = (struct an_ltv_ssidlist_new *)&areq;
	for (i = 0; i < max; i++)
		printf("SSID %2d:\t\t\t[ %.*s ]\n", i + 1, 
		    ssid->an_entry[i].an_len, 
		    ssid->an_entry[i].an_ssid);

	return;
}