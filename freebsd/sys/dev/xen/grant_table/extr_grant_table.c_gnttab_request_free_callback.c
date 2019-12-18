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
typedef  int /*<<< orphan*/  uint16_t ;
struct gnttab_free_callback {void (* fn ) (void*) ;struct gnttab_free_callback* next; int /*<<< orphan*/  count; void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_free_callbacks () ; 
 struct gnttab_free_callback* gnttab_free_callback_list ; 
 int /*<<< orphan*/  gnttab_list_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
gnttab_request_free_callback(struct gnttab_free_callback *callback,
    void (*fn)(void *), void *arg, uint16_t count)
{

	mtx_lock(&gnttab_list_lock);
	if (callback->next)
		goto out;
	callback->fn = fn;
	callback->arg = arg;
	callback->count = count;
	callback->next = gnttab_free_callback_list;
	gnttab_free_callback_list = callback;
	check_free_callbacks();
 out:
	mtx_unlock(&gnttab_list_lock);

}