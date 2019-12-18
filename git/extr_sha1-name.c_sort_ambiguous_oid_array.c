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
struct repository {int dummy; } ;
struct oid_array {int /*<<< orphan*/  nr; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT_S (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct repository*) ; 
 int /*<<< orphan*/  sort_ambiguous ; 

__attribute__((used)) static void sort_ambiguous_oid_array(struct repository *r, struct oid_array *a)
{
	QSORT_S(a->oid, a->nr, sort_ambiguous, r);
}