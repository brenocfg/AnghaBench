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
struct TYPE_4__ {char* rewrite_notes_ref; } ;
typedef  TYPE_1__ git_rebase_options ;

/* Variables and functions */
 TYPE_1__ GIT_REBASE_OPTIONS_INIT ; 
 int /*<<< orphan*/  test_copy_note (TYPE_1__*,int) ; 

void test_rebase_merge__copy_notes_specified_in_options(void)
{
	git_rebase_options opts = GIT_REBASE_OPTIONS_INIT;
	opts.rewrite_notes_ref = "refs/notes/test";

	test_copy_note(&opts, 1);
}