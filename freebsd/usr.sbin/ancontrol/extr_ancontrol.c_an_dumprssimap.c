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
struct an_ltv_rssi_map {TYPE_1__* an_entries; } ;
typedef  int /*<<< orphan*/  areq ;
struct TYPE_2__ {int an_rss_pct; int an_rss_dbm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_RID_RSSI_MAP ; 
 int /*<<< orphan*/  an_getval (char const*,struct an_req*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
an_dumprssimap(const char *iface)
{
	struct an_ltv_rssi_map	*rssi;
	struct an_req		areq;
	int                     i;

	areq.an_len = sizeof(areq);
	areq.an_type = AN_RID_RSSI_MAP;

	an_getval(iface, &areq);

	rssi = (struct an_ltv_rssi_map *)&areq;

	printf("idx\tpct\t dBm\n");

	for (i = 0; i < 0xFF; i++) {
		/* 
		 * negate the dBm value: it's the only way the power 
		 * level makes sense 
		 */
		printf("%3d\t%3d\t%4d\n", i, 
			rssi->an_entries[i].an_rss_pct,
			- rssi->an_entries[i].an_rss_dbm);
	}
}