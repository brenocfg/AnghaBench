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
struct gnttab_free_callback {scalar_t__ count; struct gnttab_free_callback* next; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct gnttab_free_callback* gnttab_free_callback_list ; 
 scalar_t__ gnttab_free_count ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_free_callbacks(void)
{
	struct gnttab_free_callback *callback, *next;

	callback = gnttab_free_callback_list;
	gnttab_free_callback_list = NULL;

	while (callback != NULL) {
		next = callback->next;
		if (gnttab_free_count >= callback->count) {
			callback->next = NULL;
			callback->fn(callback->arg);
		} else {
			callback->next = gnttab_free_callback_list;
			gnttab_free_callback_list = callback;
		}
		callback = next;
	}
}