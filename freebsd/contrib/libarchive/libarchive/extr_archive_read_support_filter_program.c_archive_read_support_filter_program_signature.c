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
struct program_bidder {int /*<<< orphan*/ * cmd; } ;
struct archive_read_filter_bidder {int dummy; } ;
struct archive_read {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 scalar_t__ ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ __archive_read_get_bidder (struct archive_read*,struct archive_read_filter_bidder**) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free_state (struct program_bidder*) ; 
 int set_bidder_signature (struct archive_read_filter_bidder*,struct program_bidder*,void const*,size_t) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
archive_read_support_filter_program_signature(struct archive *_a,
    const char *cmd, const void *signature, size_t signature_len)
{
	struct archive_read *a = (struct archive_read *)_a;
	struct archive_read_filter_bidder *bidder;
	struct program_bidder *state;

	/*
	 * Get a bidder object from the read core.
	 */
	if (__archive_read_get_bidder(a, &bidder) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/*
	 * Allocate our private state.
	 */
	state = (struct program_bidder *)calloc(1, sizeof (*state));
	if (state == NULL)
		goto memerr;
	state->cmd = strdup(cmd);
	if (state->cmd == NULL)
		goto memerr;

	return set_bidder_signature(bidder, state, signature, signature_len);
memerr:
	free_state(state);
	archive_set_error(_a, ENOMEM, "Can't allocate memory");
	return (ARCHIVE_FATAL);
}