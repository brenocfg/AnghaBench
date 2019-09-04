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
struct ref_delta_entry {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int oidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int compare_ref_delta_entry(const void *a, const void *b)
{
	const struct ref_delta_entry *delta_a = a;
	const struct ref_delta_entry *delta_b = b;

	return oidcmp(&delta_a->oid, &delta_b->oid);
}