#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ git_subtransport ;
struct TYPE_10__ {int /*<<< orphan*/  free; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/ * subtransport; } ;
typedef  TYPE_2__ git_smart_subtransport_stream ;
struct TYPE_11__ {char const* cmd; TYPE_2__ parent; int /*<<< orphan*/  io; int /*<<< orphan*/  url; } ;
typedef  TYPE_3__ git_proto_stream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_3__*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GIT_STREAM_VERSION ; 
 TYPE_3__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_3__*) ; 
 int /*<<< orphan*/  git__strdup (char const*) ; 
 int /*<<< orphan*/  git_proto_stream_free ; 
 int /*<<< orphan*/  git_proto_stream_read ; 
 int /*<<< orphan*/  git_proto_stream_write ; 
 scalar_t__ git_socket_stream_new (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int git_proto_stream_alloc(
	git_subtransport *t,
	const char *url,
	const char *cmd,
	const char *host,
	const char *port,
	git_smart_subtransport_stream **stream)
{
	git_proto_stream *s;

	if (!stream)
		return -1;

	s = git__calloc(1, sizeof(git_proto_stream));
	GIT_ERROR_CHECK_ALLOC(s);

	s->parent.subtransport = &t->parent;
	s->parent.read = git_proto_stream_read;
	s->parent.write = git_proto_stream_write;
	s->parent.free = git_proto_stream_free;

	s->cmd = cmd;
	s->url = git__strdup(url);

	if (!s->url) {
		git__free(s);
		return -1;
	}

	if ((git_socket_stream_new(&s->io, host, port)) < 0)
		return -1;

	GIT_ERROR_CHECK_VERSION(s->io, GIT_STREAM_VERSION, "git_stream");

	*stream = &s->parent;
	return 0;
}