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
struct resource_map_request {size_t size; int /*<<< orphan*/  memattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  bzero (struct resource_map_request*,size_t) ; 

void
resource_init_map_request_impl(struct resource_map_request *args, size_t sz)
{

	bzero(args, sz);
	args->size = sz;
	args->memattr = VM_MEMATTR_UNCACHEABLE;
}