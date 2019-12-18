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
struct TYPE_4__ {int /*<<< orphan*/ * message; } ;
struct TYPE_5__ {TYPE_1__ error_t; } ;
typedef  TYPE_2__ git_global_st ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void git__global_state_cleanup(git_global_st *st)
{
	if (!st)
		return;

	git__free(st->error_t.message);
	st->error_t.message = NULL;
}