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
struct vnet_sysinit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnet_sysinit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNET_SYSINIT_WLOCK () ; 
 int /*<<< orphan*/  VNET_SYSINIT_WUNLOCK () ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  vnet_constructors ; 

void
vnet_deregister_sysinit(void *arg)
{
	struct vnet_sysinit *vs;

	vs = arg;

	/* Remove the constructor from the global list of vnet constructors. */
	VNET_SYSINIT_WLOCK();
	TAILQ_REMOVE(&vnet_constructors, vs, link);
	VNET_SYSINIT_WUNLOCK();
}