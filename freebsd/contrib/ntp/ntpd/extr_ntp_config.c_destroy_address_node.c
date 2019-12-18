#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* address; } ;
typedef  TYPE_1__ address_node ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
destroy_address_node(
	address_node *my_node
	)
{
	if (NULL == my_node)
		return;
	REQUIRE(NULL != my_node->address);

	free(my_node->address);
	free(my_node);
}