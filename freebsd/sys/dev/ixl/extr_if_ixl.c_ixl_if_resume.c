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
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_if_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixl_if_resume(if_ctx_t ctx)
{
	struct ifnet *ifp = iflib_get_ifp(ctx);

	INIT_DEBUGOUT("ixl_if_resume: begin");

	/* Read & clear wake-up registers */

	/* Required after D3->D0 transition */
	if (ifp->if_flags & IFF_UP)
		ixl_if_init(ctx);

	return (0);
}