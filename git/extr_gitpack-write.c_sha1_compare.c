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
struct pack_idx_entry {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha1_compare(const void *_a, const void *_b)
{
	struct pack_idx_entry *a = *(struct pack_idx_entry **)_a;
	struct pack_idx_entry *b = *(struct pack_idx_entry **)_b;
	return oidcmp(&a->oid, &b->oid);
}