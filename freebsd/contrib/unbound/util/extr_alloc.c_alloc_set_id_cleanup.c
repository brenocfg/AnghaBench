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
struct alloc_cache {void (* cleanup ) (void*) ;void* cleanup_arg; } ;

/* Variables and functions */

void 
alloc_set_id_cleanup(struct alloc_cache* alloc, void (*cleanup)(void*),
        void* arg)
{
	alloc->cleanup = cleanup;
	alloc->cleanup_arg = arg;
}