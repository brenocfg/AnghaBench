#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct transport {scalar_t__ smart_options; int /*<<< orphan*/  family; } ;
struct remote {int dummy; } ;
struct TYPE_7__ {scalar_t__ nr; } ;
struct TYPE_6__ {scalar_t__ choice; } ;
struct TYPE_5__ {scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_NOT ; 
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_RELATIVE ; 
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_SINCE ; 
 int /*<<< orphan*/  TRANS_OPT_DEPTH ; 
 int /*<<< orphan*/  TRANS_OPT_FROM_PROMISOR ; 
 int /*<<< orphan*/  TRANS_OPT_KEEP ; 
 int /*<<< orphan*/  TRANS_OPT_LIST_OBJECTS_FILTER ; 
 int /*<<< orphan*/  TRANS_OPT_UPDATE_SHALLOW ; 
 int /*<<< orphan*/  TRANS_OPT_UPLOADPACK ; 
 int /*<<< orphan*/  add_negotiation_tips (scalar_t__) ; 
 TYPE_4__ deepen_not ; 
 scalar_t__ deepen_relative ; 
 char* deepen_since ; 
 char* depth ; 
 char* expand_list_objects_filter_spec (TYPE_2__*) ; 
 int /*<<< orphan*/  family ; 
 TYPE_2__ filter_options ; 
 scalar_t__ keep ; 
 TYPE_1__ negotiation_tip ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  set_option (struct transport*,int /*<<< orphan*/ ,char const*) ; 
 struct transport* transport_get (struct remote*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_set_verbosity (struct transport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ update_shallow ; 
 char* upload_pack ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static struct transport *prepare_transport(struct remote *remote, int deepen)
{
	struct transport *transport;

	transport = transport_get(remote, NULL);
	transport_set_verbosity(transport, verbosity, progress);
	transport->family = family;
	if (upload_pack)
		set_option(transport, TRANS_OPT_UPLOADPACK, upload_pack);
	if (keep)
		set_option(transport, TRANS_OPT_KEEP, "yes");
	if (depth)
		set_option(transport, TRANS_OPT_DEPTH, depth);
	if (deepen && deepen_since)
		set_option(transport, TRANS_OPT_DEEPEN_SINCE, deepen_since);
	if (deepen && deepen_not.nr)
		set_option(transport, TRANS_OPT_DEEPEN_NOT,
			   (const char *)&deepen_not);
	if (deepen_relative)
		set_option(transport, TRANS_OPT_DEEPEN_RELATIVE, "yes");
	if (update_shallow)
		set_option(transport, TRANS_OPT_UPDATE_SHALLOW, "yes");
	if (filter_options.choice) {
		const char *spec =
			expand_list_objects_filter_spec(&filter_options);
		set_option(transport, TRANS_OPT_LIST_OBJECTS_FILTER, spec);
		set_option(transport, TRANS_OPT_FROM_PROMISOR, "1");
	}
	if (negotiation_tip.nr) {
		if (transport->smart_options)
			add_negotiation_tips(transport->smart_options);
		else
			warning("Ignoring --negotiation-tip because the protocol does not support it.");
	}
	return transport;
}