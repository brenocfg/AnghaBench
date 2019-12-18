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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  received_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_stream_finalize_write (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_odb_stream_write (TYPE_1__*,char*,int) ; 
 TYPE_1__* stream ; 

void test_odb_streamwrite__can_accept_chunks(void)
{
	git_oid oid;

	cl_git_pass(git_odb_stream_write(stream, "deadbeef", 8));
	cl_assert_equal_sz(8, stream->received_bytes);

	cl_git_pass(git_odb_stream_write(stream, "deadbeef", 6));
	cl_assert_equal_sz(8 + 6, stream->received_bytes);

	cl_git_pass(git_odb_stream_finalize_write(&oid, stream));
}