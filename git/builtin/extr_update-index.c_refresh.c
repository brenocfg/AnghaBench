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
struct refresh_params {unsigned int flags; int /*<<< orphan*/ * has_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_cache () ; 
 int /*<<< orphan*/  refresh_cache (unsigned int) ; 
 int /*<<< orphan*/  setup_work_tree () ; 

__attribute__((used)) static int refresh(struct refresh_params *o, unsigned int flag)
{
	setup_work_tree();
	read_cache();
	*o->has_errors |= refresh_cache(o->flags | flag);
	return 0;
}