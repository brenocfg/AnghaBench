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
struct TYPE_3__ {int commit_count; char const** commits; } ;
typedef  TYPE_1__ describe_options ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char const** xrealloc (void*,size_t) ; 

__attribute__((used)) static void opts_add_commit(describe_options *opts, const char *commit)
{
	size_t sz;

	assert(opts != NULL);

	sz = ++opts->commit_count * sizeof(opts->commits[0]);
	opts->commits = xrealloc((void *) opts->commits, sz);
	opts->commits[opts->commit_count - 1] = commit;
}