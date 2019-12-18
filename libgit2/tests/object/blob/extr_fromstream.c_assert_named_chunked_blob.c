#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* write ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ git_writestream ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_create_from_stream (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_blob_create_from_stream_commit (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textual_content ; 

__attribute__((used)) static void assert_named_chunked_blob(const char *expected_sha, const char *fake_name)
{
	git_oid expected_id, id;
	git_writestream *stream;
	int i, howmany = 6;

	cl_git_pass(git_oid_fromstr(&expected_id, expected_sha));

	cl_git_pass(git_blob_create_from_stream(&stream, repo, fake_name));

	for (i = 0; i < howmany; i++)
		cl_git_pass(stream->write(stream, textual_content, strlen(textual_content)));

	cl_git_pass(git_blob_create_from_stream_commit(&id, stream));

	cl_assert_equal_oid(&expected_id, &id);
}