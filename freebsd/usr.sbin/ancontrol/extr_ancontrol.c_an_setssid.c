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
struct TYPE_2__ {int /*<<< orphan*/  an_ssid; int /*<<< orphan*/  an_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_RID_SSIDLIST ; 
 int MAX_SSIDS ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  an_setval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errx (int,char*,int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
an_setssid(const char *iface, int act, void *arg)
{
	struct an_ltv_ssidlist_new	*ssid;
	struct an_req		areq;
	int			max;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_SSIDLIST;

	an_getval(iface, &areq);
	ssid = (struct an_ltv_ssidlist_new *)&areq;

	max = (areq.an_len - 4) / sizeof(struct an_ltv_ssid_entry);
	if ( max > MAX_SSIDS ) {
		printf("Too many SSIDs only printing %d of %d\n",
		    MAX_SSIDS, max);
		max = MAX_SSIDS;
	}

	if ( act > max ) {
		errx(1, "bad modifier %d: there "
		    "are only %d SSID settings", act, max);
		exit(1);
	}

	bzero(ssid->an_entry[act-1].an_ssid, 
	    sizeof(ssid->an_entry[act-1].an_ssid));
	strlcpy(ssid->an_entry[act-1].an_ssid, (char *)arg, 
	    sizeof(ssid->an_entry[act-1].an_ssid));
	ssid->an_entry[act-1].an_len 
	    = strlen(ssid->an_entry[act-1].an_ssid);

	an_setval(iface, &areq);

	exit(0);
}