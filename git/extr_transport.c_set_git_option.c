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
struct string_list {int dummy; } ;
struct git_transport_options {char const* uploadpack; char const* receivepack; int thin; int followtags; int keep; int update_shallow; char const* deepen_since; int deepen_relative; int from_promisor; int no_dependents; int /*<<< orphan*/  filter_options; struct string_list const* deepen_not; scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_NOT ; 
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_RELATIVE ; 
 int /*<<< orphan*/  TRANS_OPT_DEEPEN_SINCE ; 
 int /*<<< orphan*/  TRANS_OPT_DEPTH ; 
 int /*<<< orphan*/  TRANS_OPT_FOLLOWTAGS ; 
 int /*<<< orphan*/  TRANS_OPT_FROM_PROMISOR ; 
 int /*<<< orphan*/  TRANS_OPT_KEEP ; 
 int /*<<< orphan*/  TRANS_OPT_LIST_OBJECTS_FILTER ; 
 int /*<<< orphan*/  TRANS_OPT_NO_DEPENDENTS ; 
 int /*<<< orphan*/  TRANS_OPT_RECEIVEPACK ; 
 int /*<<< orphan*/  TRANS_OPT_THIN ; 
 int /*<<< orphan*/  TRANS_OPT_UPDATE_SHALLOW ; 
 int /*<<< orphan*/  TRANS_OPT_UPLOADPACK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  list_objects_filter_die_if_populated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_list_objects_filter (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_git_option(struct git_transport_options *opts,
			  const char *name, const char *value)
{
	if (!strcmp(name, TRANS_OPT_UPLOADPACK)) {
		opts->uploadpack = value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_RECEIVEPACK)) {
		opts->receivepack = value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_THIN)) {
		opts->thin = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_FOLLOWTAGS)) {
		opts->followtags = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_KEEP)) {
		opts->keep = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_UPDATE_SHALLOW)) {
		opts->update_shallow = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_DEPTH)) {
		if (!value)
			opts->depth = 0;
		else {
			char *end;
			opts->depth = strtol(value, &end, 0);
			if (*end)
				die(_("transport: invalid depth option '%s'"), value);
		}
		return 0;
	} else if (!strcmp(name, TRANS_OPT_DEEPEN_SINCE)) {
		opts->deepen_since = value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_DEEPEN_NOT)) {
		opts->deepen_not = (const struct string_list *)value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_DEEPEN_RELATIVE)) {
		opts->deepen_relative = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_FROM_PROMISOR)) {
		opts->from_promisor = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_NO_DEPENDENTS)) {
		opts->no_dependents = !!value;
		return 0;
	} else if (!strcmp(name, TRANS_OPT_LIST_OBJECTS_FILTER)) {
		list_objects_filter_die_if_populated(&opts->filter_options);
		parse_list_objects_filter(&opts->filter_options, value);
		return 0;
	}
	return 1;
}