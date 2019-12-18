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
struct TYPE_4__ {int (* next ) (int /*<<< orphan*/ **,TYPE_1__*) ;} ;
typedef  TYPE_1__ git_config_iterator ;
typedef  int /*<<< orphan*/  git_config_entry ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ **,TYPE_1__*) ; 

int git_config_next(git_config_entry **entry, git_config_iterator *iter)
{
	return iter->next(entry, iter);
}