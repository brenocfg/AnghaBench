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
struct amba_id {int mask; int id; } ;
struct amba_device {int periphid; scalar_t__ cid; } ;

/* Variables and functions */
 scalar_t__ CORESIGHT_CID ; 
 scalar_t__ amba_cs_uci_id_match (struct amba_id const*,struct amba_device*) ; 

__attribute__((used)) static const struct amba_id *
amba_lookup(const struct amba_id *table, struct amba_device *dev)
{
	while (table->mask) {
		if (((dev->periphid & table->mask) == table->id) &&
			((dev->cid != CORESIGHT_CID) ||
			 (amba_cs_uci_id_match(table, dev))))
			return table;
		table++;
	}
	return NULL;
}