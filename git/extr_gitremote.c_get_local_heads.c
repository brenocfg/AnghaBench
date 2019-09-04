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
struct ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,struct ref***) ; 
 int /*<<< orphan*/  one_local_ref ; 

struct ref *get_local_heads(void)
{
	struct ref *local_refs = NULL, **local_tail = &local_refs;

	for_each_ref(one_local_ref, &local_tail);
	return local_refs;
}