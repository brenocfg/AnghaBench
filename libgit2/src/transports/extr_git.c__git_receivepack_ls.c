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
struct TYPE_9__ {TYPE_2__* current_stream; } ;
typedef  TYPE_1__ git_subtransport ;
typedef  int /*<<< orphan*/  git_smart_subtransport_stream ;
struct TYPE_10__ {int /*<<< orphan*/  io; } ;
typedef  TYPE_2__ git_proto_stream ;
struct TYPE_11__ {int /*<<< orphan*/  port; int /*<<< orphan*/  host; } ;
typedef  TYPE_3__ git_net_url ;

/* Variables and functions */
 TYPE_3__ GIT_NET_URL_INIT ; 
 int /*<<< orphan*/  cmd_receivepack ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_net_url_dispose (TYPE_3__*) ; 
 int git_net_url_parse (TYPE_3__*,char const*) ; 
 int git_proto_stream_alloc (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_proto_stream_free (int /*<<< orphan*/ *) ; 
 int git_stream_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix_git ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _git_receivepack_ls(
	git_subtransport *t,
	const char *url,
	git_smart_subtransport_stream **stream)
{
	git_net_url urldata = GIT_NET_URL_INIT;
	const char *stream_url = url;
	git_proto_stream *s;
	int error;

	*stream = NULL;
	if (!git__prefixcmp(url, prefix_git))
		stream_url += strlen(prefix_git);

	if ((error = git_net_url_parse(&urldata, url)) < 0)
		return error;

	error = git_proto_stream_alloc(t, stream_url, cmd_receivepack, urldata.host, urldata.port, stream);

	git_net_url_dispose(&urldata);

	if (error < 0) {
		git_proto_stream_free(*stream);
		return error;
	}

	s = (git_proto_stream *) *stream;

	if ((error = git_stream_connect(s->io)) < 0)
		return error;

	t->current_stream = s;

	return 0;
}