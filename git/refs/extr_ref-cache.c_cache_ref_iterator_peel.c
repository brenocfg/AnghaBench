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
struct ref_iterator {int /*<<< orphan*/  oid; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int peel_object (int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int cache_ref_iterator_peel(struct ref_iterator *ref_iterator,
				   struct object_id *peeled)
{
	return peel_object(ref_iterator->oid, peeled);
}