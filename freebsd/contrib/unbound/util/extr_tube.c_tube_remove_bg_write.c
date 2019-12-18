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
struct tube_res_list {struct tube_res_list* buf; struct tube_res_list* next; } ;
struct tube {int /*<<< orphan*/ * res_last; struct tube_res_list* res_list; int /*<<< orphan*/ * res_com; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tube_res_list*) ; 

void tube_remove_bg_write(struct tube* tube)
{
	if(tube->res_com) {
		comm_point_delete(tube->res_com);
		tube->res_com = NULL;
	}
	if(tube->res_list) {
		struct tube_res_list* np, *p = tube->res_list;
		tube->res_list = NULL;
		tube->res_last = NULL;
		while(p) {
			np = p->next;
			free(p->buf);
			free(p);
			p = np;
		}
	}
}