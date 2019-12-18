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
struct transport {int verbose; int /*<<< orphan*/  pack_lockfile; struct ref* remote_refs; int /*<<< orphan*/  server_options; int /*<<< orphan*/  stateless_rpc; int /*<<< orphan*/  cloning; int /*<<< orphan*/  progress; struct git_transport_data* data; } ;
struct ref {int /*<<< orphan*/  exact_oid; } ;
struct TYPE_2__ {int /*<<< orphan*/  connectivity_checked; int /*<<< orphan*/  self_contained_and_connected; int /*<<< orphan*/  negotiation_tips; int /*<<< orphan*/  filter_options; int /*<<< orphan*/  no_dependents; int /*<<< orphan*/  from_promisor; int /*<<< orphan*/  update_shallow; int /*<<< orphan*/  check_self_contained_and_connected; int /*<<< orphan*/  deepen_relative; int /*<<< orphan*/  deepen_not; int /*<<< orphan*/  deepen_since; int /*<<< orphan*/  depth; int /*<<< orphan*/  followtags; int /*<<< orphan*/  thin; int /*<<< orphan*/  keep; int /*<<< orphan*/  uploadpack; } ;
struct git_transport_data {int version; TYPE_1__ options; scalar_t__ got_remote_heads; int /*<<< orphan*/ * conn; int /*<<< orphan*/ * fd; int /*<<< orphan*/  shallow; } ;
struct fetch_pack_args {int lock_pack; int verbose; int quiet; int no_progress; int /*<<< orphan*/  connectivity_checked; int /*<<< orphan*/  self_contained_and_connected; int /*<<< orphan*/  negotiation_tips; int /*<<< orphan*/  server_options; int /*<<< orphan*/  stateless_rpc; int /*<<< orphan*/  filter_options; int /*<<< orphan*/  no_dependents; int /*<<< orphan*/  from_promisor; int /*<<< orphan*/  update_shallow; int /*<<< orphan*/  cloning; int /*<<< orphan*/  check_self_contained_and_connected; int /*<<< orphan*/  deepen_relative; int /*<<< orphan*/  deepen_not; int /*<<< orphan*/  deepen_since; int /*<<< orphan*/  depth; int /*<<< orphan*/  include_tag; int /*<<< orphan*/  use_thin_pack; int /*<<< orphan*/  keep_pack; int /*<<< orphan*/  uploadpack; } ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_if_server_options (struct transport*) ; 
 struct ref* fetch_pack (struct fetch_pack_args*,int /*<<< orphan*/ *,struct ref*,struct ref**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ finish_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_refs (struct ref*) ; 
 struct ref* handshake (struct transport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct fetch_pack_args*,int /*<<< orphan*/ ,int) ; 
#define  protocol_unknown_version 131 
#define  protocol_v0 130 
#define  protocol_v1 129 
#define  protocol_v2 128 
 scalar_t__ report_unmatched_refs (struct ref**,int) ; 

__attribute__((used)) static int fetch_refs_via_pack(struct transport *transport,
			       int nr_heads, struct ref **to_fetch)
{
	int ret = 0;
	struct git_transport_data *data = transport->data;
	struct ref *refs = NULL;
	struct fetch_pack_args args;
	struct ref *refs_tmp = NULL;

	memset(&args, 0, sizeof(args));
	args.uploadpack = data->options.uploadpack;
	args.keep_pack = data->options.keep;
	args.lock_pack = 1;
	args.use_thin_pack = data->options.thin;
	args.include_tag = data->options.followtags;
	args.verbose = (transport->verbose > 1);
	args.quiet = (transport->verbose < 0);
	args.no_progress = !transport->progress;
	args.depth = data->options.depth;
	args.deepen_since = data->options.deepen_since;
	args.deepen_not = data->options.deepen_not;
	args.deepen_relative = data->options.deepen_relative;
	args.check_self_contained_and_connected =
		data->options.check_self_contained_and_connected;
	args.cloning = transport->cloning;
	args.update_shallow = data->options.update_shallow;
	args.from_promisor = data->options.from_promisor;
	args.no_dependents = data->options.no_dependents;
	args.filter_options = data->options.filter_options;
	args.stateless_rpc = transport->stateless_rpc;
	args.server_options = transport->server_options;
	args.negotiation_tips = data->options.negotiation_tips;

	if (!data->got_remote_heads) {
		int i;
		int must_list_refs = 0;
		for (i = 0; i < nr_heads; i++) {
			if (!to_fetch[i]->exact_oid) {
				must_list_refs = 1;
				break;
			}
		}
		refs_tmp = handshake(transport, 0, NULL, must_list_refs);
	}

	switch (data->version) {
	case protocol_v2:
		refs = fetch_pack(&args, data->fd,
				  refs_tmp ? refs_tmp : transport->remote_refs,
				  to_fetch, nr_heads, &data->shallow,
				  &transport->pack_lockfile, data->version);
		break;
	case protocol_v1:
	case protocol_v0:
		die_if_server_options(transport);
		refs = fetch_pack(&args, data->fd,
				  refs_tmp ? refs_tmp : transport->remote_refs,
				  to_fetch, nr_heads, &data->shallow,
				  &transport->pack_lockfile, data->version);
		break;
	case protocol_unknown_version:
		BUG("unknown protocol version");
	}

	close(data->fd[0]);
	close(data->fd[1]);
	if (finish_connect(data->conn))
		ret = -1;
	data->conn = NULL;
	data->got_remote_heads = 0;
	data->options.self_contained_and_connected =
		args.self_contained_and_connected;
	data->options.connectivity_checked = args.connectivity_checked;

	if (refs == NULL)
		ret = -1;
	if (report_unmatched_refs(to_fetch, nr_heads))
		ret = -1;

	free_refs(refs_tmp);
	free_refs(refs);
	return ret;
}