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
struct patch {char* old_name; char* new_name; unsigned int ws_rule; unsigned int inaccurate_eof; scalar_t__ is_binary; struct fragment* fragments; } ;
struct image {int dummy; } ;
struct fragment {char* oldpos; int rejected; struct fragment* next; } ;
struct apply_state {int /*<<< orphan*/  apply_with_reject; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int apply_binary (struct apply_state*,struct image*,struct patch*) ; 
 scalar_t__ apply_one_fragment (struct apply_state*,struct image*,struct fragment*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static int apply_fragments(struct apply_state *state, struct image *img, struct patch *patch)
{
	struct fragment *frag = patch->fragments;
	const char *name = patch->old_name ? patch->old_name : patch->new_name;
	unsigned ws_rule = patch->ws_rule;
	unsigned inaccurate_eof = patch->inaccurate_eof;
	int nth = 0;

	if (patch->is_binary)
		return apply_binary(state, img, patch);

	while (frag) {
		nth++;
		if (apply_one_fragment(state, img, frag, inaccurate_eof, ws_rule, nth)) {
			error(_("patch failed: %s:%ld"), name, frag->oldpos);
			if (!state->apply_with_reject)
				return -1;
			frag->rejected = 1;
		}
		frag = frag->next;
	}
	return 0;
}