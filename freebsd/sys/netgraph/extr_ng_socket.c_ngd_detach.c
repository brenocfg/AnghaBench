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
struct socket {int dummy; } ;
struct ngpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NG_DATA ; 
 int /*<<< orphan*/  ng_detach_common (struct ngpcb* const,int /*<<< orphan*/ ) ; 
 struct ngpcb* sotongpcb (struct socket*) ; 

__attribute__((used)) static void
ngd_detach(struct socket *so)
{
	struct ngpcb *const pcbp = sotongpcb(so);

	KASSERT(pcbp != NULL, ("ngd_detach: pcbp == NULL"));
	ng_detach_common(pcbp, NG_DATA);
}