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
struct strbuf {int dummy; } ;
struct promisor_remote {int /*<<< orphan*/  partial_clone_filter; } ;
struct list_objects_filter_options {int /*<<< orphan*/  filter_spec; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  gently_parse_list_objects_filter (struct list_objects_filter_options*,int /*<<< orphan*/ ,struct strbuf*) ; 
 struct promisor_remote* promisor_remote_find (char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void partial_clone_get_default_filter_spec(
	struct list_objects_filter_options *filter_options,
	const char *remote)
{
	struct promisor_remote *promisor = promisor_remote_find(remote);
	struct strbuf errbuf = STRBUF_INIT;

	/*
	 * Parse default value, but silently ignore it if it is invalid.
	 */
	if (!promisor)
		return;

	string_list_append(&filter_options->filter_spec,
			   promisor->partial_clone_filter);
	gently_parse_list_objects_filter(filter_options,
					 promisor->partial_clone_filter,
					 &errbuf);
	strbuf_release(&errbuf);
}