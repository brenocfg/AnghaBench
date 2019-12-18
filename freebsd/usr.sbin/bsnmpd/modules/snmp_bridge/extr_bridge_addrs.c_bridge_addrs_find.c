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
struct tp_entry {scalar_t__ sysindex; int /*<<< orphan*/  tp_addr; } ;
struct bridge_if {scalar_t__ sysindex; struct tp_entry* f_tpa; } ;

/* Variables and functions */
 struct tp_entry* TAILQ_NEXT (struct tp_entry*,int /*<<< orphan*/ ) ; 
 scalar_t__ bridge_compare_macs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tp_e ; 

struct tp_entry *
bridge_addrs_find(uint8_t *mac, struct bridge_if *bif)
{
	struct tp_entry *te;

	for (te = bif->f_tpa; te != NULL; te = TAILQ_NEXT(te, tp_e)) {
		if (te->sysindex != bif->sysindex) {
			te = NULL;
			break;
		}

		if (bridge_compare_macs(te->tp_addr, mac) == 0)
			break;
	}

	return (te);
}