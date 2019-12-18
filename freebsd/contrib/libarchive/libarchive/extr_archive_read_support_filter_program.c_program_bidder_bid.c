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
struct program_bidder {scalar_t__ signature_len; int inhibit; int /*<<< orphan*/  signature; } ;
struct archive_read_filter_bidder {struct program_bidder* data; } ;
struct archive_read_filter {int dummy; } ;

/* Variables and functions */
 int INT_MAX ; 
 char* __archive_read_filter_ahead (struct archive_read_filter*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
program_bidder_bid(struct archive_read_filter_bidder *self,
    struct archive_read_filter *upstream)
{
	struct program_bidder *state = self->data;
	const char *p;

	/* If we have a signature, use that to match. */
	if (state->signature_len > 0) {
		p = __archive_read_filter_ahead(upstream,
		    state->signature_len, NULL);
		if (p == NULL)
			return (0);
		/* No match, so don't bid. */
		if (memcmp(p, state->signature, state->signature_len) != 0)
			return (0);
		return ((int)state->signature_len * 8);
	}

	/* Otherwise, bid once and then never bid again. */
	if (state->inhibit)
		return (0);
	state->inhibit = 1;
	return (INT_MAX);
}