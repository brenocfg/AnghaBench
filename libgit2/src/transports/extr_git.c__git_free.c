#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  current_stream; } ;
typedef  TYPE_1__ git_subtransport ;
typedef  int /*<<< orphan*/  git_smart_subtransport ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

__attribute__((used)) static void _git_free(git_smart_subtransport *subtransport)
{
	git_subtransport *t = (git_subtransport *) subtransport;

	assert(!t->current_stream);

	git__free(t);
}