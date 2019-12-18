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
struct TYPE_7__ {int sent_command; int /*<<< orphan*/  io; int /*<<< orphan*/  url; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_1__ git_proto_stream ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int gen_proto (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_stream__write_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_command(git_proto_stream *s)
{
	git_buf request = GIT_BUF_INIT;
	int error;

	if ((error = gen_proto(&request, s->cmd, s->url)) < 0)
		goto cleanup;

	if ((error = git_stream__write_full(s->io, request.ptr, request.size, 0)) < 0)
		goto cleanup;

	s->sent_command = 1;

cleanup:
	git_buf_dispose(&request);
	return error;
}