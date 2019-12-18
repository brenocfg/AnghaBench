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
struct rm_args {int /*<<< orphan*/  ra_flags; int /*<<< orphan*/  ra_desc; int /*<<< orphan*/  ra_rm; } ;

/* Variables and functions */
 int /*<<< orphan*/  rm_init_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rm_sysinit(void *arg)
{
	struct rm_args *args;

	args = arg;
	rm_init_flags(args->ra_rm, args->ra_desc, args->ra_flags);
}