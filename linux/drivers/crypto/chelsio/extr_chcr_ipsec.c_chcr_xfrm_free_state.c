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
struct TYPE_2__ {scalar_t__ offload_handle; } ;
struct xfrm_state {TYPE_1__ xso; } ;
struct ipsec_sa_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct ipsec_sa_entry*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chcr_xfrm_free_state(struct xfrm_state *x)
{
	struct ipsec_sa_entry *sa_entry;

	if (!x->xso.offload_handle)
		return;

	sa_entry = (struct ipsec_sa_entry *)x->xso.offload_handle;
	kfree(sa_entry);
	module_put(THIS_MODULE);
}