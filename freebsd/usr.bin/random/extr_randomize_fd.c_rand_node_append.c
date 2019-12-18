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
struct rand_node {struct rand_node* next; } ;

/* Variables and functions */
 struct rand_node* rand_root ; 
 struct rand_node* rand_tail ; 

__attribute__((used)) static void
rand_node_append(struct rand_node *n)
{
	if (rand_root == NULL)
		rand_root = rand_tail = n;
	else {
		rand_tail->next = n;
		rand_tail = n;
	}
}