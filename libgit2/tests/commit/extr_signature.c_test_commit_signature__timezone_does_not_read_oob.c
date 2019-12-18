#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  time; } ;
struct TYPE_8__ {TYPE_1__ when; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_signature__parse (TYPE_2__*,char const**,char const*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_signature_free (TYPE_2__*) ; 
 int strlen (char const*) ; 

void test_commit_signature__timezone_does_not_read_oob(void)
{
	const char *header = "A <a@example.com> 1461698487 +1234", *header_end;
	git_signature *sig;

	/* Let the buffer end midway between the timezone offeset's "+12" and "34" */
	header_end = header + strlen(header) - 2;

	sig = git__calloc(1, sizeof(git_signature));
	cl_assert(sig);

	cl_git_pass(git_signature__parse(sig, &header, header_end, NULL, '\0'));
	cl_assert_equal_s(sig->name, "A");
	cl_assert_equal_s(sig->email, "a@example.com");
	cl_assert_equal_i(sig->when.time, 1461698487);
	cl_assert_equal_i(sig->when.offset, 12);

	git_signature_free(sig);
}