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
struct name_entry {scalar_t__ mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_null_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int same_entry(struct name_entry *a, struct name_entry *b)
{
	return	!is_null_oid(&a->oid) &&
		!is_null_oid(&b->oid) &&
		oideq(&a->oid, &b->oid) &&
		a->mode == b->mode;
}