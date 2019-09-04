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
struct pack_midx_entry {scalar_t__ pack_mtime; int pack_int_id; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int midx_oid_compare(const void *_a, const void *_b)
{
	const struct pack_midx_entry *a = (const struct pack_midx_entry *)_a;
	const struct pack_midx_entry *b = (const struct pack_midx_entry *)_b;
	int cmp = oidcmp(&a->oid, &b->oid);

	if (cmp)
		return cmp;

	if (a->pack_mtime > b->pack_mtime)
		return -1;
	else if (a->pack_mtime < b->pack_mtime)
		return 1;

	return a->pack_int_id - b->pack_int_id;
}