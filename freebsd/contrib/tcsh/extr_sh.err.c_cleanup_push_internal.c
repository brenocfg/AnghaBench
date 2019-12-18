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
struct cleanup_entry {void (* fn ) (void*) ;char const* file; size_t line; void* var; } ;

/* Variables and functions */
 int cleanup_sp ; 
 struct cleanup_entry* cleanup_stack ; 
 int cleanup_stack_size ; 
 struct cleanup_entry* xrealloc (struct cleanup_entry*,int) ; 

void
cleanup_push_internal(void *var, void (*fn) (void *)
#ifdef CLEANUP_DEBUG
    , const char *file, size_t line
#endif
)
{
    struct cleanup_entry *ce;

    if (cleanup_sp == cleanup_stack_size) {
	if (cleanup_stack_size == 0)
	    cleanup_stack_size = 64; /* Arbitrary */
	else
	    cleanup_stack_size *= 2;
	cleanup_stack = xrealloc(cleanup_stack,
				 cleanup_stack_size * sizeof (*cleanup_stack));
    }
    ce = cleanup_stack + cleanup_sp;
    ce->var = var;
    ce->fn = fn;
#ifdef CLEANUP_DEBUG
    ce->file = file;
    ce->line = line;
#endif
    cleanup_sp++;
}