#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ git_blame__origin ;

/* Variables and functions */

__attribute__((used)) static git_blame__origin *origin_incref(git_blame__origin *o)
{
	if (o)
		o->refcnt++;
	return o;
}