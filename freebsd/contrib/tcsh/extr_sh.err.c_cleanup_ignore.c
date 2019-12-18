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
struct cleanup_entry {void* var; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cleanup_ignore_fn ; 
 int cleanup_sp ; 
 struct cleanup_entry* cleanup_stack ; 

void
cleanup_ignore(void *var)
{
    struct cleanup_entry *ce;

    ce = cleanup_stack + cleanup_sp;
    while (ce != cleanup_stack) {
        ce--;
	if (ce->var == var) {
	    ce->fn = cleanup_ignore_fn;
	    return;
	}
    }
    abort();
}