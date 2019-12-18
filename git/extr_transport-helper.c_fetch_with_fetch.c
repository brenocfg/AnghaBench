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
struct transport {int /*<<< orphan*/  pack_lockfile; struct helper_data* data; } ;
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
struct ref {int status; scalar_t__ name; scalar_t__ symref; int /*<<< orphan*/  old_oid; } ;
struct TYPE_2__ {int self_contained_and_connected; scalar_t__ check_self_contained_and_connected; } ;
struct helper_data {int /*<<< orphan*/  name; TYPE_1__ transport_options; scalar_t__ check_connectivity; } ;

/* Variables and functions */
 int REF_STATUS_UPTODATE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ recvline (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  sendline (struct helper_data*,struct strbuf*) ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static int fetch_with_fetch(struct transport *transport,
			    int nr_heads, struct ref **to_fetch)
{
	struct helper_data *data = transport->data;
	int i;
	struct strbuf buf = STRBUF_INIT;

	for (i = 0; i < nr_heads; i++) {
		const struct ref *posn = to_fetch[i];
		if (posn->status & REF_STATUS_UPTODATE)
			continue;

		strbuf_addf(&buf, "fetch %s %s\n",
			    oid_to_hex(&posn->old_oid),
			    posn->symref ? posn->symref : posn->name);
	}

	strbuf_addch(&buf, '\n');
	sendline(data, &buf);

	while (1) {
		if (recvline(data, &buf))
			exit(128);

		if (starts_with(buf.buf, "lock ")) {
			const char *name = buf.buf + 5;
			if (transport->pack_lockfile)
				warning(_("%s also locked %s"), data->name, name);
			else
				transport->pack_lockfile = xstrdup(name);
		}
		else if (data->check_connectivity &&
			 data->transport_options.check_self_contained_and_connected &&
			 !strcmp(buf.buf, "connectivity-ok"))
			data->transport_options.self_contained_and_connected = 1;
		else if (!buf.len)
			break;
		else
			warning(_("%s unexpectedly said: '%s'"), data->name, buf.buf);
	}
	strbuf_release(&buf);
	return 0;
}