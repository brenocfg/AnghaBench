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
struct transport {scalar_t__ cloning; TYPE_1__* vtable; struct helper_data* data; } ;
struct ref {int status; } ;
struct TYPE_6__ {scalar_t__ choice; } ;
struct TYPE_5__ {scalar_t__ negotiation_tips; TYPE_3__ filter_options; scalar_t__ update_shallow; scalar_t__ check_self_contained_and_connected; } ;
struct helper_data {scalar_t__ import; scalar_t__ fetch; TYPE_2__ transport_options; scalar_t__ check_connectivity; int /*<<< orphan*/  get_refs_list_called; } ;
struct TYPE_4__ {int (* fetch ) (struct transport*,int,struct ref**) ;} ;

/* Variables and functions */
 int REF_STATUS_UPTODATE ; 
 int /*<<< orphan*/  do_take_over (struct transport*) ; 
 char* expand_list_objects_filter_spec (TYPE_3__*) ; 
 int fetch_with_fetch (struct transport*,int,struct ref**) ; 
 int fetch_with_import (struct transport*,int,struct ref**) ; 
 int /*<<< orphan*/  get_helper (struct transport*) ; 
 int /*<<< orphan*/  get_refs_list_using_list (struct transport*,int /*<<< orphan*/ ) ; 
 scalar_t__ process_connect (struct transport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_helper_option (struct transport*,char*,char const*) ; 
 int stub1 (struct transport*,int,struct ref**) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static int fetch(struct transport *transport,
		 int nr_heads, struct ref **to_fetch)
{
	struct helper_data *data = transport->data;
	int i, count;

	get_helper(transport);

	if (process_connect(transport, 0)) {
		do_take_over(transport);
		return transport->vtable->fetch(transport, nr_heads, to_fetch);
	}

	if (!data->get_refs_list_called)
		get_refs_list_using_list(transport, 0);

	count = 0;
	for (i = 0; i < nr_heads; i++)
		if (!(to_fetch[i]->status & REF_STATUS_UPTODATE))
			count++;

	if (!count)
		return 0;

	if (data->check_connectivity &&
	    data->transport_options.check_self_contained_and_connected)
		set_helper_option(transport, "check-connectivity", "true");

	if (transport->cloning)
		set_helper_option(transport, "cloning", "true");

	if (data->transport_options.update_shallow)
		set_helper_option(transport, "update-shallow", "true");

	if (data->transport_options.filter_options.choice) {
		const char *spec = expand_list_objects_filter_spec(
			&data->transport_options.filter_options);
		set_helper_option(transport, "filter", spec);
	}

	if (data->transport_options.negotiation_tips)
		warning("Ignoring --negotiation-tip because the protocol does not support it.");

	if (data->fetch)
		return fetch_with_fetch(transport, nr_heads, to_fetch);

	if (data->import)
		return fetch_with_import(transport, nr_heads, to_fetch);

	return -1;
}