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
struct sigev_node {int dummy; } ;
typedef  int /*<<< orphan*/  sigev_id_t ;

/* Variables and functions */
 int __sigev_delete_node (struct sigev_node*) ; 
 struct sigev_node* __sigev_find (int,int /*<<< orphan*/ ) ; 

int
__sigev_delete(int type, sigev_id_t id)
{
	struct sigev_node *sn;

	sn = __sigev_find(type, id);
	if (sn != NULL)
		return (__sigev_delete_node(sn));
	return (0);
}