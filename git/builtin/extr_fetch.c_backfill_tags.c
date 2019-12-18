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
struct transport {int /*<<< orphan*/  remote; int /*<<< orphan*/  cannot_reuse; } ;
struct ref {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_RELATIVE ; 
 int /*<<< orphan*/  TRANS_OPT_DEPTH ; 
 int /*<<< orphan*/  TRANS_OPT_FOLLOWTAGS ; 
 int /*<<< orphan*/  consume_refs (struct transport*,struct ref*) ; 
 TYPE_1__ deepen_not ; 
 scalar_t__ deepen_since ; 
 int /*<<< orphan*/  fetch_refs (struct transport*,struct ref*) ; 
 struct transport* gsecondary ; 
 struct transport* prepare_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_disconnect (struct transport*) ; 
 int /*<<< orphan*/  transport_set_option (struct transport*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void backfill_tags(struct transport *transport, struct ref *ref_map)
{
	int cannot_reuse;

	/*
	 * Once we have set TRANS_OPT_DEEPEN_SINCE, we can't unset it
	 * when remote helper is used (setting it to an empty string
	 * is not unsetting). We could extend the remote helper
	 * protocol for that, but for now, just force a new connection
	 * without deepen-since. Similar story for deepen-not.
	 */
	cannot_reuse = transport->cannot_reuse ||
		deepen_since || deepen_not.nr;
	if (cannot_reuse) {
		gsecondary = prepare_transport(transport->remote, 0);
		transport = gsecondary;
	}

	transport_set_option(transport, TRANS_OPT_FOLLOWTAGS, NULL);
	transport_set_option(transport, TRANS_OPT_DEPTH, "0");
	transport_set_option(transport, TRANS_OPT_DEEPEN_RELATIVE, NULL);
	if (!fetch_refs(transport, ref_map))
		consume_refs(transport, ref_map);

	if (gsecondary) {
		transport_disconnect(gsecondary);
		gsecondary = NULL;
	}
}