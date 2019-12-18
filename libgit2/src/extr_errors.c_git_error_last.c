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
typedef  int /*<<< orphan*/  git_error ;
struct TYPE_2__ {int /*<<< orphan*/  const* last_error; } ;

/* Variables and functions */
 TYPE_1__* GIT_GLOBAL ; 

const git_error *git_error_last(void)
{
	return GIT_GLOBAL->last_error;
}