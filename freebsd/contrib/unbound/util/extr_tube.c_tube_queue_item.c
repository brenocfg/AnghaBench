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
typedef  int /*<<< orphan*/  uint8_t ;
struct tube_res_list {size_t len; struct tube_res_list* next; int /*<<< orphan*/ * buf; } ;
struct tube {int /*<<< orphan*/  res_com; struct tube_res_list* res_last; struct tube_res_list* res_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_start_listening (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 

int tube_queue_item(struct tube* tube, uint8_t* msg, size_t len)
{
	struct tube_res_list* item;
	if(!tube || !tube->res_com) return 0;
	item = (struct tube_res_list*)malloc(sizeof(*item));
	if(!item) {
		free(msg);
		log_err("out of memory for async answer");
		return 0;
	}
	item->buf = msg;
	item->len = len;
	item->next = NULL;
	/* add at back of list, since the first one may be partially written */
	if(tube->res_last)
		tube->res_last->next = item;
	else    tube->res_list = item;
	tube->res_last = item;
	if(tube->res_list == tube->res_last) {
		/* first added item, start the write process */
		comm_point_start_listening(tube->res_com, -1, -1);
	}
	return 1;
}