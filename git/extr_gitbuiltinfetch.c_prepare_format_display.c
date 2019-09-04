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
struct ref {scalar_t__ status; int /*<<< orphan*/  name; int /*<<< orphan*/  peer_ref; struct ref* next; } ;

/* Variables and functions */
 scalar_t__ REF_STATUS_REJECT_SHALLOW ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  adjust_refcol_width (struct ref*) ; 
 int compact_format ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_config_get_string_const (char*,char const**) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void prepare_format_display(struct ref *ref_map)
{
	struct ref *rm;
	const char *format = "full";

	git_config_get_string_const("fetch.output", &format);
	if (!strcasecmp(format, "full"))
		compact_format = 0;
	else if (!strcasecmp(format, "compact"))
		compact_format = 1;
	else
		die(_("configuration fetch.output contains invalid value %s"),
		    format);

	for (rm = ref_map; rm; rm = rm->next) {
		if (rm->status == REF_STATUS_REJECT_SHALLOW ||
		    !rm->peer_ref ||
		    !strcmp(rm->name, "HEAD"))
			continue;

		adjust_refcol_width(rm);
	}
}