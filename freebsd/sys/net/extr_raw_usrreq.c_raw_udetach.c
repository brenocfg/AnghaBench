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
struct rawcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  raw_detach (struct rawcb*) ; 
 struct rawcb* sotorawcb (struct socket*) ; 

__attribute__((used)) static void
raw_udetach(struct socket *so)
{
	struct rawcb *rp = sotorawcb(so);

	KASSERT(rp != NULL, ("raw_udetach: rp == NULL"));

	raw_detach(rp);
}