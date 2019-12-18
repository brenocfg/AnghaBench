#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct ref {int dummy; } ;
struct oidset {int dummy; } ;
struct TYPE_6__ {scalar_t__ choice; } ;
struct fetch_pack_args {scalar_t__ no_dependents; TYPE_3__ filter_options; scalar_t__ deepen; scalar_t__ include_tag; scalar_t__ no_progress; scalar_t__ use_thin_pack; TYPE_2__* server_options; } ;
struct fetch_negotiator {int dummy; } ;
struct TYPE_5__ {int nr; TYPE_1__* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_common (struct strbuf*,struct oidset*) ; 
 int add_haves (struct fetch_negotiator*,struct strbuf*,int*,int*) ; 
 int /*<<< orphan*/  add_shallow_requests (struct strbuf*,struct fetch_pack_args*) ; 
 int /*<<< orphan*/  add_wants (scalar_t__,struct ref const*,struct strbuf*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 char* expand_list_objects_filter_spec (TYPE_3__*) ; 
 int /*<<< orphan*/  git_user_agent_sanitized () ; 
 scalar_t__ is_repository_shallow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_buf_delim (struct strbuf*) ; 
 int /*<<< orphan*/  packet_buf_flush (struct strbuf*) ; 
 int /*<<< orphan*/  packet_buf_write (struct strbuf*,char*,...) ; 
 scalar_t__ prefer_ofs_delta ; 
 int /*<<< orphan*/  print_verbose (struct fetch_pack_args*,int /*<<< orphan*/ ) ; 
 scalar_t__ server_supports_feature (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ server_supports_v2 (char*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  warning (char*) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_fetch_request(struct fetch_negotiator *negotiator, int fd_out,
			      struct fetch_pack_args *args,
			      const struct ref *wants, struct oidset *common,
			      int *haves_to_send, int *in_vain,
			      int sideband_all)
{
	int ret = 0;
	struct strbuf req_buf = STRBUF_INIT;

	if (server_supports_v2("fetch", 1))
		packet_buf_write(&req_buf, "command=fetch");
	if (server_supports_v2("agent", 0))
		packet_buf_write(&req_buf, "agent=%s", git_user_agent_sanitized());
	if (args->server_options && args->server_options->nr &&
	    server_supports_v2("server-option", 1)) {
		int i;
		for (i = 0; i < args->server_options->nr; i++)
			packet_buf_write(&req_buf, "server-option=%s",
					 args->server_options->items[i].string);
	}

	packet_buf_delim(&req_buf);
	if (args->use_thin_pack)
		packet_buf_write(&req_buf, "thin-pack");
	if (args->no_progress)
		packet_buf_write(&req_buf, "no-progress");
	if (args->include_tag)
		packet_buf_write(&req_buf, "include-tag");
	if (prefer_ofs_delta)
		packet_buf_write(&req_buf, "ofs-delta");
	if (sideband_all)
		packet_buf_write(&req_buf, "sideband-all");

	/* Add shallow-info and deepen request */
	if (server_supports_feature("fetch", "shallow", 0))
		add_shallow_requests(&req_buf, args);
	else if (is_repository_shallow(the_repository) || args->deepen)
		die(_("Server does not support shallow requests"));

	/* Add filter */
	if (server_supports_feature("fetch", "filter", 0) &&
	    args->filter_options.choice) {
		const char *spec =
			expand_list_objects_filter_spec(&args->filter_options);
		print_verbose(args, _("Server supports filter"));
		packet_buf_write(&req_buf, "filter %s", spec);
	} else if (args->filter_options.choice) {
		warning("filtering not recognized by server, ignoring");
	}

	/* add wants */
	add_wants(args->no_dependents, wants, &req_buf);

	if (args->no_dependents) {
		packet_buf_write(&req_buf, "done");
		ret = 1;
	} else {
		/* Add all of the common commits we've found in previous rounds */
		add_common(&req_buf, common);

		/* Add initial haves */
		ret = add_haves(negotiator, &req_buf, haves_to_send, in_vain);
	}

	/* Send request */
	packet_buf_flush(&req_buf);
	if (write_in_full(fd_out, req_buf.buf, req_buf.len) < 0)
		die_errno(_("unable to write request to remote"));

	strbuf_release(&req_buf);
	return ret;
}