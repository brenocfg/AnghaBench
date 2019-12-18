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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct rpc_state {char* service_name; int in; int out; int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * protocol_header; int /*<<< orphan*/ * hdr_accept; int /*<<< orphan*/ * hdr_content_type; int /*<<< orphan*/ * service_url; scalar_t__ pos; int /*<<< orphan*/  alloc; } ;
struct discovery {int /*<<< orphan*/  version; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct child_process {int in; int out; int git_cmd; char const** argv; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ get_protocol_http_header (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  http_post_buffer ; 
 int packet_read (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int post_rpc (struct rpc_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,...) ; 
 void* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_1__ url ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xmalloc (int /*<<< orphan*/ ) ; 
 scalar_t__ xread (int,char*,int) ; 

__attribute__((used)) static int rpc_service(struct rpc_state *rpc, struct discovery *heads,
		       const char **client_argv, const struct strbuf *preamble,
		       struct strbuf *rpc_result)
{
	const char *svc = rpc->service_name;
	struct strbuf buf = STRBUF_INIT;
	struct child_process client = CHILD_PROCESS_INIT;
	int err = 0;

	client.in = -1;
	client.out = -1;
	client.git_cmd = 1;
	client.argv = client_argv;
	if (start_command(&client))
		exit(1);
	write_or_die(client.in, preamble->buf, preamble->len);
	if (heads)
		write_or_die(client.in, heads->buf, heads->len);

	rpc->alloc = http_post_buffer;
	rpc->buf = xmalloc(rpc->alloc);
	rpc->in = client.in;
	rpc->out = client.out;

	strbuf_addf(&buf, "%s%s", url.buf, svc);
	rpc->service_url = strbuf_detach(&buf, NULL);

	strbuf_addf(&buf, "Content-Type: application/x-%s-request", svc);
	rpc->hdr_content_type = strbuf_detach(&buf, NULL);

	strbuf_addf(&buf, "Accept: application/x-%s-result", svc);
	rpc->hdr_accept = strbuf_detach(&buf, NULL);

	if (get_protocol_http_header(heads->version, &buf))
		rpc->protocol_header = strbuf_detach(&buf, NULL);
	else
		rpc->protocol_header = NULL;

	while (!err) {
		int n = packet_read(rpc->out, NULL, NULL, rpc->buf, rpc->alloc, 0);
		if (!n)
			break;
		rpc->pos = 0;
		rpc->len = n;
		err |= post_rpc(rpc, 0);
	}

	close(client.in);
	client.in = -1;
	if (!err) {
		strbuf_read(rpc_result, client.out, 0);
	} else {
		char buf[4096];
		for (;;)
			if (xread(client.out, buf, sizeof(buf)) <= 0)
				break;
	}

	close(client.out);
	client.out = -1;

	err |= finish_command(&client);
	free(rpc->service_url);
	free(rpc->hdr_content_type);
	free(rpc->hdr_accept);
	free(rpc->protocol_header);
	free(rpc->buf);
	strbuf_release(&buf);
	return err;
}