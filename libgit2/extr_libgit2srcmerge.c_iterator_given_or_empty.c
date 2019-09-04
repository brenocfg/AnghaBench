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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 scalar_t__ git_iterator_for_nothing (int /*<<< orphan*/ **,TYPE_1__*) ; 

__attribute__((used)) static git_iterator *iterator_given_or_empty(git_iterator **empty, git_iterator *given)
{
	git_iterator_options opts = GIT_ITERATOR_OPTIONS_INIT;

	if (given)
		return given;

	opts.flags = GIT_ITERATOR_DONT_IGNORE_CASE;

	if (git_iterator_for_nothing(empty, &opts) < 0)
		return NULL;

	return *empty;
}