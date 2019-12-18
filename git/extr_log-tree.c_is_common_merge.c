#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct commit {TYPE_2__* parents; } ;
struct TYPE_4__ {TYPE_1__* next; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */

__attribute__((used)) static int is_common_merge(const struct commit *commit)
{
	return (commit->parents
		&& commit->parents->next
		&& !commit->parents->next->next);
}