#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_13__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  id_num; } ;
struct TYPE_11__ {int /*<<< orphan*/  id_num; } ;
struct TYPE_10__ {struct TYPE_10__* last; struct TYPE_10__* next; TYPE_3__ request; int /*<<< orphan*/  time; } ;
typedef  TYPE_1__ TABLE_ENTRY ;
typedef  TYPE_2__ CTL_RESPONSE ;
typedef  TYPE_3__ CTL_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int /*<<< orphan*/  LOG_ERR ; 
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  new_id () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* table ; 
 TYPE_4__ ts ; 

void
insert_table(CTL_MSG *request, CTL_RESPONSE *response)
{
	TABLE_ENTRY *ptr;
	time_t current_time;

	clock_gettime(CLOCK_MONOTONIC_FAST, &ts);
	current_time = ts.tv_sec;
	request->id_num = new_id();
	response->id_num = htonl(request->id_num);
	/* insert a new entry into the top of the list */
	ptr = (TABLE_ENTRY *)malloc(sizeof(TABLE_ENTRY));
	if (ptr == NIL) {
		syslog(LOG_ERR, "insert_table: Out of memory");
		_exit(1);
	}
	ptr->time = current_time;
	ptr->request = *request;
	ptr->next = table;
	if (ptr->next != NIL)
		ptr->next->last = ptr;
	ptr->last = NIL;
	table = ptr;
}