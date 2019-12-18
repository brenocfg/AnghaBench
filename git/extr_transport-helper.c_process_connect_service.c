#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct transport {int stateless_rpc; struct helper_data* data; } ;
struct strbuf {int dummy; } ;
struct helper_data {scalar_t__ stateless_connect; scalar_t__ connect; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ get_protocol_version_config () ; 
 scalar_t__ protocol_v2 ; 
 int run_connect (struct transport*,struct strbuf*) ; 
 int set_helper_option (struct transport*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_connect_service(struct transport *transport,
				   const char *name, const char *exec)
{
	struct helper_data *data = transport->data;
	struct strbuf cmdbuf = STRBUF_INIT;
	int ret = 0;

	/*
	 * Handle --upload-pack and friends. This is fire and forget...
	 * just warn if it fails.
	 */
	if (strcmp(name, exec)) {
		int r = set_helper_option(transport, "servpath", exec);
		if (r > 0)
			warning(_("setting remote service path not supported by protocol"));
		else if (r < 0)
			warning(_("invalid remote service path"));
	}

	if (data->connect) {
		strbuf_addf(&cmdbuf, "connect %s\n", name);
		ret = run_connect(transport, &cmdbuf);
	} else if (data->stateless_connect &&
		   (get_protocol_version_config() == protocol_v2) &&
		   !strcmp("git-upload-pack", name)) {
		strbuf_addf(&cmdbuf, "stateless-connect %s\n", name);
		ret = run_connect(transport, &cmdbuf);
		if (ret)
			transport->stateless_rpc = 1;
	}

	strbuf_release(&cmdbuf);
	return ret;
}