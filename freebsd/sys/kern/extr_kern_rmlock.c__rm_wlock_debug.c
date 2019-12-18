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
struct rmlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rm_wlock (struct rmlock*) ; 

void
_rm_wlock_debug(struct rmlock *rm, const char *file, int line)
{

	_rm_wlock(rm);
}