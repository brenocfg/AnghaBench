#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmci_handle {int dummy; } ;
struct TYPE_2__ {struct vmci_handle handle; } ;
struct vmci_resource {TYPE_1__ hash_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_resource*) ; 

struct vmci_handle
vmci_resource_handle(struct vmci_resource *resource)
{

	ASSERT(resource);
	return (resource->hash_entry.handle);
}