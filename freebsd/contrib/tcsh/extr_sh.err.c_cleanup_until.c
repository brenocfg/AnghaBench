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
struct cleanup_entry {void* var; int /*<<< orphan*/  (* fn ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 size_t cleanup_sp ; 
 struct cleanup_entry* cleanup_stack ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void
cleanup_until(void *last_var)
{
    while (cleanup_sp != 0) {
	struct cleanup_entry ce;

	cleanup_sp--;
	ce = cleanup_stack[cleanup_sp];
	ce.fn(ce.var);
	if (ce.var == last_var)
	    return;
    }
    abort();
}