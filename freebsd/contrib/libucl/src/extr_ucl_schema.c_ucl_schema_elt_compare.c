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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_compare_node {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int ucl_object_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ucl_schema_elt_compare (struct ucl_compare_node *n1, struct ucl_compare_node *n2)
{
	const ucl_object_t *o1 = n1->obj, *o2 = n2->obj;

	return ucl_object_compare (o1, o2);
}