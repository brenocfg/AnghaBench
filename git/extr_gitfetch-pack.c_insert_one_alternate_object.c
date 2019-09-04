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
struct object {int /*<<< orphan*/  oid; } ;
struct fetch_negotiator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rev_list_insert_ref (struct fetch_negotiator*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void insert_one_alternate_object(struct fetch_negotiator *negotiator,
					struct object *obj)
{
	rev_list_insert_ref(negotiator, NULL, &obj->oid);
}