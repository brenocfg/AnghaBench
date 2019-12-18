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
struct bridge_if {int /*<<< orphan*/  sysindex; int /*<<< orphan*/  bif_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bridge_addrs_dump (struct bridge_if*) ; 
 struct bridge_if* bridge_first_bif () ; 
 struct bridge_if* bridge_next_bif (struct bridge_if*) ; 
 int /*<<< orphan*/  bridge_ports_dump (struct bridge_if*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bridge_ifs_dump(void)
{
	struct bridge_if *bif;

	for (bif = bridge_first_bif(); bif != NULL;
		bif = bridge_next_bif(bif)) {
		syslog(LOG_ERR, "Bridge %s, index - %d", bif->bif_name,
		    bif->sysindex);
		bridge_ports_dump(bif);
		bridge_addrs_dump(bif);
	}
}