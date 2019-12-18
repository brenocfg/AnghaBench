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
struct ref {scalar_t__ status; int /*<<< orphan*/  name; struct ref* next; } ;

/* Variables and functions */
 scalar_t__ REF_STATUS_NONE ; 
 scalar_t__ REF_STATUS_OK ; 
 scalar_t__ REF_STATUS_REJECT_ALREADY_EXISTS ; 
 scalar_t__ REF_STATUS_REJECT_FETCH_FIRST ; 
 scalar_t__ REF_STATUS_REJECT_NEEDS_FORCE ; 
 scalar_t__ REF_STATUS_REJECT_NONFASTFORWARD ; 
 scalar_t__ REF_STATUS_UPTODATE ; 
 unsigned int REJECT_ALREADY_EXISTS ; 
 unsigned int REJECT_FETCH_FIRST ; 
 unsigned int REJECT_NEEDS_FORCE ; 
 unsigned int REJECT_NON_FF_HEAD ; 
 unsigned int REJECT_NON_FF_OTHER ; 
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ print_one_push_status (struct ref*,char const*,int,int,int) ; 
 char* resolve_refdup (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ transport_color_config () ; 
 int transport_summary_width (struct ref*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

void transport_print_push_status(const char *dest, struct ref *refs,
				  int verbose, int porcelain, unsigned int *reject_reasons)
{
	struct ref *ref;
	int n = 0;
	char *head;
	int summary_width = transport_summary_width(refs);

	if (transport_color_config() < 0)
		warning(_("could not parse transport.color.* config"));

	head = resolve_refdup("HEAD", RESOLVE_REF_READING, NULL, NULL);

	if (verbose) {
		for (ref = refs; ref; ref = ref->next)
			if (ref->status == REF_STATUS_UPTODATE)
				n += print_one_push_status(ref, dest, n,
							   porcelain, summary_width);
	}

	for (ref = refs; ref; ref = ref->next)
		if (ref->status == REF_STATUS_OK)
			n += print_one_push_status(ref, dest, n,
						   porcelain, summary_width);

	*reject_reasons = 0;
	for (ref = refs; ref; ref = ref->next) {
		if (ref->status != REF_STATUS_NONE &&
		    ref->status != REF_STATUS_UPTODATE &&
		    ref->status != REF_STATUS_OK)
			n += print_one_push_status(ref, dest, n,
						   porcelain, summary_width);
		if (ref->status == REF_STATUS_REJECT_NONFASTFORWARD) {
			if (head != NULL && !strcmp(head, ref->name))
				*reject_reasons |= REJECT_NON_FF_HEAD;
			else
				*reject_reasons |= REJECT_NON_FF_OTHER;
		} else if (ref->status == REF_STATUS_REJECT_ALREADY_EXISTS) {
			*reject_reasons |= REJECT_ALREADY_EXISTS;
		} else if (ref->status == REF_STATUS_REJECT_FETCH_FIRST) {
			*reject_reasons |= REJECT_FETCH_FIRST;
		} else if (ref->status == REF_STATUS_REJECT_NEEDS_FORCE) {
			*reject_reasons |= REJECT_NEEDS_FORCE;
		}
	}
	free(head);
}