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
struct partition_entry {scalar_t__* index; } ;
struct asn_oid {int len; scalar_t__* subs; } ;

/* Variables and functions */

__attribute__((used)) static int
partition_idx_cmp(const struct asn_oid *oid, u_int sub,
    const struct partition_entry *entry)
{
	u_int i;

	for (i = 0; i < 2 && i < oid->len - sub; i++) {
		if (oid->subs[sub + i] < entry->index[i])
			return (-1);
		if (oid->subs[sub + i] > entry->index[i])
			return (+1);
	}
	if (oid->len - sub < 2)
		return (-1);
	if (oid->len - sub > 2)
		return (+1);

	return (0);
}