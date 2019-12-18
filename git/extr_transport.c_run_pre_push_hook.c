#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct transport {char* url; TYPE_1__* remote; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct ref {scalar_t__ status; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; int /*<<< orphan*/  new_oid; TYPE_2__* peer_ref; struct ref* next; } ;
struct child_process {char const** argv; int in; char* trace2_hook_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 scalar_t__ EPIPE ; 
 scalar_t__ REF_STATUS_REJECT_NONFASTFORWARD ; 
 scalar_t__ REF_STATUS_REJECT_STALE ; 
 scalar_t__ REF_STATUS_UPTODATE ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int close (int) ; 
 scalar_t__ errno ; 
 char* find_hook (char*) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_pre_push_hook(struct transport *transport,
			     struct ref *remote_refs)
{
	int ret = 0, x;
	struct ref *r;
	struct child_process proc = CHILD_PROCESS_INIT;
	struct strbuf buf;
	const char *argv[4];

	if (!(argv[0] = find_hook("pre-push")))
		return 0;

	argv[1] = transport->remote->name;
	argv[2] = transport->url;
	argv[3] = NULL;

	proc.argv = argv;
	proc.in = -1;
	proc.trace2_hook_name = "pre-push";

	if (start_command(&proc)) {
		finish_command(&proc);
		return -1;
	}

	sigchain_push(SIGPIPE, SIG_IGN);

	strbuf_init(&buf, 256);

	for (r = remote_refs; r; r = r->next) {
		if (!r->peer_ref) continue;
		if (r->status == REF_STATUS_REJECT_NONFASTFORWARD) continue;
		if (r->status == REF_STATUS_REJECT_STALE) continue;
		if (r->status == REF_STATUS_UPTODATE) continue;

		strbuf_reset(&buf);
		strbuf_addf( &buf, "%s %s %s %s\n",
			 r->peer_ref->name, oid_to_hex(&r->new_oid),
			 r->name, oid_to_hex(&r->old_oid));

		if (write_in_full(proc.in, buf.buf, buf.len) < 0) {
			/* We do not mind if a hook does not read all refs. */
			if (errno != EPIPE)
				ret = -1;
			break;
		}
	}

	strbuf_release(&buf);

	x = close(proc.in);
	if (!ret)
		ret = x;

	sigchain_pop(SIGPIPE);

	x = finish_command(&proc);
	if (!ret)
		ret = x;

	return ret;
}