#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* current_stream; } ;
typedef  TYPE_1__ git_subtransport ;
typedef  int /*<<< orphan*/  git_smart_subtransport_stream ;
struct TYPE_6__ {int /*<<< orphan*/  io; } ;
typedef  TYPE_2__ git_proto_stream ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DEFAULT_PORT ; 
 int /*<<< orphan*/  cmd_receivepack ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 int git_proto_stream_alloc (TYPE_1__*,char const*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_proto_stream_free (int /*<<< orphan*/ *) ; 
 int git_stream_connect (int /*<<< orphan*/ ) ; 
 int gitno_extract_url_parts (char**,char**,char**,char**,char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix_git ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _git_receivepack_ls(
	git_subtransport *t,
	const char *url,
	git_smart_subtransport_stream **stream)
{
	char *host=NULL, *port=NULL, *path=NULL, *user=NULL, *pass=NULL;
	const char *stream_url = url;
	git_proto_stream *s;
	int error;

	*stream = NULL;
	if (!git__prefixcmp(url, prefix_git))
		stream_url += strlen(prefix_git);

	if ((error = gitno_extract_url_parts(&host, &port, &path, &user, &pass, url, GIT_DEFAULT_PORT)) < 0)
		return error;

	error = git_proto_stream_alloc(t, stream_url, cmd_receivepack, host, port, stream);

	git__free(host);
	git__free(port);
	git__free(path);
	git__free(user);
	git__free(pass);

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