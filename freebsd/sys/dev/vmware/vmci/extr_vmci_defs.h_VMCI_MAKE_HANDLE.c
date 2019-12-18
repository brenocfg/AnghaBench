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
typedef  void* vmci_id ;
struct vmci_handle {void* resource; void* context; } ;

/* Variables and functions */

__attribute__((used)) static inline struct vmci_handle
VMCI_MAKE_HANDLE(vmci_id cid, vmci_id rid)
{
	struct vmci_handle h;

	h.context = cid;
	h.resource = rid;
	return (h);
}