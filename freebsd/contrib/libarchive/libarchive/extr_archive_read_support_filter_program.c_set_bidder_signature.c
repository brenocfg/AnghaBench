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
struct program_bidder {size_t signature_len; int /*<<< orphan*/  signature; } ;
struct archive_read_filter_bidder {int /*<<< orphan*/  free; int /*<<< orphan*/ * options; int /*<<< orphan*/  init; int /*<<< orphan*/  bid; struct program_bidder* data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  program_bidder_bid ; 
 int /*<<< orphan*/  program_bidder_free ; 
 int /*<<< orphan*/  program_bidder_init ; 

__attribute__((used)) static int
set_bidder_signature(struct archive_read_filter_bidder *bidder,
    struct program_bidder *state, const void *signature, size_t signature_len)
{

	if (signature != NULL && signature_len > 0) {
		state->signature_len = signature_len;
		state->signature = malloc(signature_len);
		memcpy(state->signature, signature, signature_len);
	}

	/*
	 * Fill in the bidder object.
	 */
	bidder->data = state;
	bidder->bid = program_bidder_bid;
	bidder->init = program_bidder_init;
	bidder->options = NULL;
	bidder->free = program_bidder_free;
	return (ARCHIVE_OK);
}