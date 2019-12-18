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
typedef  int /*<<< orphan*/  uint8_t ;
struct tp_entry {int /*<<< orphan*/  tp_addr; int /*<<< orphan*/  sysindex; } ;
struct bridge_if {int /*<<< orphan*/  f_tpa; int /*<<< orphan*/  sysindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bridge_addrs_bif_insert (int /*<<< orphan*/ *,struct tp_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct tp_entry*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_entries ; 

struct tp_entry *
bridge_new_addrs(uint8_t *mac, struct bridge_if *bif)
{
	struct tp_entry *te;

	if ((te = (struct tp_entry *) malloc(sizeof(*te))) == NULL) {
		syslog(LOG_ERR, "bridge new address: failed: %s",
		    strerror(errno));
		return (NULL);
	}

	bzero(te, sizeof(*te));

	te->sysindex = bif->sysindex;
	bcopy(mac, te->tp_addr, ETHER_ADDR_LEN);
	bridge_addrs_bif_insert(&tp_entries, te, &(bif->f_tpa));

	return (te);
}