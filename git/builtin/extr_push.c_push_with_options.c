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
struct transport {char* url; TYPE_1__* smart_options; int /*<<< orphan*/  family; } ;
struct refspec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_OPT_NAME ; 
 int /*<<< orphan*/  PUSH_COLOR_ERROR ; 
 int /*<<< orphan*/  PUSH_COLOR_RESET ; 
 unsigned int REJECT_ALREADY_EXISTS ; 
 unsigned int REJECT_FETCH_FIRST ; 
 unsigned int REJECT_NEEDS_FORCE ; 
 unsigned int REJECT_NON_FF_HEAD ; 
 unsigned int REJECT_NON_FF_OTHER ; 
 int /*<<< orphan*/  TRANS_OPT_RECEIVEPACK ; 
 int /*<<< orphan*/  TRANS_OPT_THIN ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  advise_checkout_pull_push () ; 
 int /*<<< orphan*/  advise_pull_before_push () ; 
 int /*<<< orphan*/  advise_ref_already_exists () ; 
 int /*<<< orphan*/  advise_ref_fetch_first () ; 
 int /*<<< orphan*/  advise_ref_needs_force () ; 
 int /*<<< orphan*/  cas ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  family ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  is_empty_cas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  progress ; 
 char* push_get_color (int /*<<< orphan*/ ) ; 
 char* receivepack ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ thin ; 
 int /*<<< orphan*/  trace2_region_enter (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_region_leave (char*,char*,int /*<<< orphan*/ ) ; 
 int transport_disconnect (struct transport*) ; 
 int transport_push (int /*<<< orphan*/ ,struct transport*,struct refspec*,int,unsigned int*) ; 
 int /*<<< orphan*/  transport_set_option (struct transport*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transport_set_verbosity (struct transport*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int push_with_options(struct transport *transport, struct refspec *rs,
			     int flags)
{
	int err;
	unsigned int reject_reasons;

	transport_set_verbosity(transport, verbosity, progress);
	transport->family = family;

	if (receivepack)
		transport_set_option(transport,
				     TRANS_OPT_RECEIVEPACK, receivepack);
	transport_set_option(transport, TRANS_OPT_THIN, thin ? "yes" : NULL);

	if (!is_empty_cas(&cas)) {
		if (!transport->smart_options)
			die("underlying transport does not support --%s option",
			    CAS_OPT_NAME);
		transport->smart_options->cas = &cas;
	}

	if (verbosity > 0)
		fprintf(stderr, _("Pushing to %s\n"), transport->url);
	trace2_region_enter("push", "transport_push", the_repository);
	err = transport_push(the_repository, transport,
			     rs, flags, &reject_reasons);
	trace2_region_leave("push", "transport_push", the_repository);
	if (err != 0) {
		fprintf(stderr, "%s", push_get_color(PUSH_COLOR_ERROR));
		error(_("failed to push some refs to '%s'"), transport->url);
		fprintf(stderr, "%s", push_get_color(PUSH_COLOR_RESET));
	}

	err |= transport_disconnect(transport);
	if (!err)
		return 0;

	if (reject_reasons & REJECT_NON_FF_HEAD) {
		advise_pull_before_push();
	} else if (reject_reasons & REJECT_NON_FF_OTHER) {
		advise_checkout_pull_push();
	} else if (reject_reasons & REJECT_ALREADY_EXISTS) {
		advise_ref_already_exists();
	} else if (reject_reasons & REJECT_FETCH_FIRST) {
		advise_ref_fetch_first();
	} else if (reject_reasons & REJECT_NEEDS_FORCE) {
		advise_ref_needs_force();
	}

	return 1;
}