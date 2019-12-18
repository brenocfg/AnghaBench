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
struct vmci_resource {int /*<<< orphan*/  container_object; int /*<<< orphan*/  (* container_free_cb ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_resource*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inline
vmci_resource_do_remove(struct vmci_resource *resource)
{

	ASSERT(resource);

	if (resource->container_free_cb) {
		resource->container_free_cb(resource->container_object);
		/* Resource has been freed don't dereference it. */
	}
}