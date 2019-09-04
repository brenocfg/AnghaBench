#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int skip_tree; scalar_t__ next_idx; TYPE_1__ base; } ;
typedef  TYPE_2__ index_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_FIRST_ACCESS ; 

__attribute__((used)) static int index_iterator_init(index_iterator *iter)
{
	iter->base.flags &= ~GIT_ITERATOR_FIRST_ACCESS;
	iter->next_idx = 0;
	iter->skip_tree = false;
	return 0;
}