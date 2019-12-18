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
struct quick_exit_handler {int /*<<< orphan*/  (* cleanup ) () ;struct quick_exit_handler* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  _Exit (int) ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 struct quick_exit_handler* handlers ; 
 int /*<<< orphan*/  stub1 () ; 

void
quick_exit(int status)
{
	struct quick_exit_handler *h;

	/*
	 * XXX: The C++ spec requires us to call std::terminate if there is an
	 * exception here.
	 */
	for (h = handlers; NULL != h; h = h->next) {
		__compiler_membar();
		h->cleanup();
	}
	_Exit(status);
}