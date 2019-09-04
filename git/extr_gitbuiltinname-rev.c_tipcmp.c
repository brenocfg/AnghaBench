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
struct tip_table_entry {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tipcmp(const void *a_, const void *b_)
{
	const struct tip_table_entry *a = a_, *b = b_;
	return oidcmp(&a->oid, &b->oid);
}