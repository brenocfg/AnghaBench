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
struct stat {int dummy; } ;
struct patch {scalar_t__ is_delete; int /*<<< orphan*/  resultsize; int /*<<< orphan*/  result; scalar_t__ direct_to_threeway; } ;
struct image {int /*<<< orphan*/  line_allocated; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct cache_entry {int dummy; } ;
struct apply_state {int /*<<< orphan*/  threeway; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_to_fn_table (struct apply_state*,struct patch*) ; 
 scalar_t__ apply_fragments (struct apply_state*,struct image*,struct patch*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ load_preimage (struct apply_state*,struct image*,struct patch*,struct stat*,struct cache_entry const*) ; 
 scalar_t__ try_threeway (struct apply_state*,struct image*,struct patch*,struct stat*,struct cache_entry const*) ; 

__attribute__((used)) static int apply_data(struct apply_state *state, struct patch *patch,
		      struct stat *st, const struct cache_entry *ce)
{
	struct image image;

	if (load_preimage(state, &image, patch, st, ce) < 0)
		return -1;

	if (patch->direct_to_threeway ||
	    apply_fragments(state, &image, patch) < 0) {
		/* Note: with --reject, apply_fragments() returns 0 */
		if (!state->threeway || try_threeway(state, &image, patch, st, ce) < 0)
			return -1;
	}
	patch->result = image.buf;
	patch->resultsize = image.len;
	add_to_fn_table(state, patch);
	free(image.line_allocated);

	if (0 < patch->is_delete && patch->resultsize)
		return error(_("removal patch leaves file contents"));

	return 0;
}