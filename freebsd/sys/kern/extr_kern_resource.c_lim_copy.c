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
struct plimit {int pl_refcnt; int /*<<< orphan*/  pl_rlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
lim_copy(struct plimit *dst, struct plimit *src)
{

	KASSERT(dst->pl_refcnt <= 1, ("lim_copy to shared limit"));
	bcopy(src->pl_rlimit, dst->pl_rlimit, sizeof(src->pl_rlimit));
}