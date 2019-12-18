#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_13__ {scalar_t__ tv_sec; } ;
struct TYPE_12__ {scalar_t__ type; scalar_t__ pid; int /*<<< orphan*/  l_name; int /*<<< orphan*/  r_name; } ;
struct TYPE_11__ {scalar_t__ time; TYPE_2__ request; struct TYPE_11__* next; } ;
typedef  TYPE_1__ TABLE_ENTRY ;
typedef  TYPE_2__ CTL_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 scalar_t__ MAX_LIFE ; 
 TYPE_1__* NIL ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  delete (TYPE_1__*) ; 
 int /*<<< orphan*/  print_request (char*,TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* table ; 
 TYPE_3__ ts ; 

CTL_MSG *
find_request(CTL_MSG *request)
{
	TABLE_ENTRY *ptr, *next;
	time_t current_time;

	clock_gettime(CLOCK_MONOTONIC_FAST, &ts);
	current_time = ts.tv_sec;
	/*
	 * See if this is a repeated message, and check for
	 * out of date entries in the table while we are it.
	 */
	if (debug)
		print_request("find_request", request);
	for (ptr = table; ptr != NIL; ptr = next) {
		next = ptr->next;
		if ((ptr->time - current_time) > MAX_LIFE) {
			/* the entry is too old */
			if (debug)
				print_request("deleting expired entry",
				    &ptr->request);
			delete(ptr);
			continue;
		}
		if (debug)
			print_request("", &ptr->request);
		if (strcmp(request->r_name, ptr->request.r_name) == 0 &&
		    strcmp(request->l_name, ptr->request.l_name) == 0 &&
		    request->type == ptr->request.type &&
		    request->pid == ptr->request.pid) {
			/* update the time if we 'touch' it */
			ptr->time = current_time;
			return (&ptr->request);
		}
	}
	return ((CTL_MSG *)0);
}