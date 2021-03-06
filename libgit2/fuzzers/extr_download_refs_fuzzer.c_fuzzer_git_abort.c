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
struct TYPE_3__ {char* message; } ;
typedef  TYPE_1__ git_error ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  stderr ; 

void fuzzer_git_abort(const char *op)
{
	const git_error *err = git_error_last();
	fprintf(stderr, "unexpected libgit error: %s: %s\n",
		op, err ? err->message : "<none>");
	abort();
}