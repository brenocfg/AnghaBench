#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct commit {TYPE_1__* parents; } ;
struct TYPE_2__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */

__attribute__((used)) static int patch_id_defined(struct commit *commit)
{
	/* must be 0 or 1 parents */
	return !commit->parents || !commit->parents->next;
}