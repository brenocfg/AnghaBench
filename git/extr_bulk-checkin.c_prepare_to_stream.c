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
struct bulk_checkin_state {int /*<<< orphan*/  offset; scalar_t__ f; int /*<<< orphan*/  pack_idx_opts; int /*<<< orphan*/  pack_tmp_name; } ;

/* Variables and functions */
 unsigned int HASH_WRITE_OBJECT ; 
 scalar_t__ create_tmp_packfile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  reset_pack_idx_option (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pack_header (scalar_t__,int) ; 

__attribute__((used)) static void prepare_to_stream(struct bulk_checkin_state *state,
			      unsigned flags)
{
	if (!(flags & HASH_WRITE_OBJECT) || state->f)
		return;

	state->f = create_tmp_packfile(&state->pack_tmp_name);
	reset_pack_idx_option(&state->pack_idx_opts);

	/* Pretend we are going to write only one object */
	state->offset = write_pack_header(state->f, 1);
	if (!state->offset)
		die_errno("unable to write pack header");
}