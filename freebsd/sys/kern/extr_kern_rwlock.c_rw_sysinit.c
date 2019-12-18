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
struct rwlock {int dummy; } ;
struct rw_args {int /*<<< orphan*/  ra_flags; int /*<<< orphan*/  ra_desc; scalar_t__ ra_rw; } ;

/* Variables and functions */
 int /*<<< orphan*/  rw_init_flags (struct rwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rw_sysinit(void *arg)
{
	struct rw_args *args;

	args = arg;
	rw_init_flags((struct rwlock *)args->ra_rw, args->ra_desc,
	    args->ra_flags);
}