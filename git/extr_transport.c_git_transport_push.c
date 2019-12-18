#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct transport {scalar_t__ verbose; int /*<<< orphan*/  url; int /*<<< orphan*/  push_options; int /*<<< orphan*/  progress; struct git_transport_data* data; } ;
struct send_pack_args {int send_mirror; int force_update; int verbose; int quiet; int dry_run; int porcelain; int atomic; int /*<<< orphan*/  push_cert; int /*<<< orphan*/  url; int /*<<< orphan*/  push_options; int /*<<< orphan*/  progress; int /*<<< orphan*/  use_thin_pack; } ;
struct ref {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  thin; } ;
struct git_transport_data {int version; scalar_t__ got_remote_heads; int /*<<< orphan*/ * conn; int /*<<< orphan*/ * fd; int /*<<< orphan*/  extra_have; TYPE_1__ options; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_ALWAYS ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_IF_ASKED ; 
 int /*<<< orphan*/  SEND_PACK_PUSH_CERT_NEVER ; 
 int TRANSPORT_PUSH_ATOMIC ; 
 int TRANSPORT_PUSH_CERT_ALWAYS ; 
 int TRANSPORT_PUSH_CERT_IF_ASKED ; 
 int TRANSPORT_PUSH_DRY_RUN ; 
 int TRANSPORT_PUSH_FORCE ; 
 int TRANSPORT_PUSH_MIRROR ; 
 int TRANSPORT_PUSH_PORCELAIN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int finish_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_refs_via_connect (struct transport*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct send_pack_args*,int /*<<< orphan*/ ,int) ; 
#define  protocol_unknown_version 131 
#define  protocol_v0 130 
#define  protocol_v1 129 
#define  protocol_v2 128 
 int send_pack (struct send_pack_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ref*,int /*<<< orphan*/ *) ; 
 scalar_t__ transport_color_config () ; 

__attribute__((used)) static int git_transport_push(struct transport *transport, struct ref *remote_refs, int flags)
{
	struct git_transport_data *data = transport->data;
	struct send_pack_args args;
	int ret = 0;

	if (transport_color_config() < 0)
		return -1;

	if (!data->got_remote_heads)
		get_refs_via_connect(transport, 1, NULL);

	memset(&args, 0, sizeof(args));
	args.send_mirror = !!(flags & TRANSPORT_PUSH_MIRROR);
	args.force_update = !!(flags & TRANSPORT_PUSH_FORCE);
	args.use_thin_pack = data->options.thin;
	args.verbose = (transport->verbose > 0);
	args.quiet = (transport->verbose < 0);
	args.progress = transport->progress;
	args.dry_run = !!(flags & TRANSPORT_PUSH_DRY_RUN);
	args.porcelain = !!(flags & TRANSPORT_PUSH_PORCELAIN);
	args.atomic = !!(flags & TRANSPORT_PUSH_ATOMIC);
	args.push_options = transport->push_options;
	args.url = transport->url;

	if (flags & TRANSPORT_PUSH_CERT_ALWAYS)
		args.push_cert = SEND_PACK_PUSH_CERT_ALWAYS;
	else if (flags & TRANSPORT_PUSH_CERT_IF_ASKED)
		args.push_cert = SEND_PACK_PUSH_CERT_IF_ASKED;
	else
		args.push_cert = SEND_PACK_PUSH_CERT_NEVER;

	switch (data->version) {
	case protocol_v2:
		die(_("support for protocol v2 not implemented yet"));
		break;
	case protocol_v1:
	case protocol_v0:
		ret = send_pack(&args, data->fd, data->conn, remote_refs,
				&data->extra_have);
		break;
	case protocol_unknown_version:
		BUG("unknown protocol version");
	}

	close(data->fd[1]);
	close(data->fd[0]);
	ret |= finish_connect(data->conn);
	data->conn = NULL;
	data->got_remote_heads = 0;

	return ret;
}