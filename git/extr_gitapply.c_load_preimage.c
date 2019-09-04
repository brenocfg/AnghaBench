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
struct strbuf {int dummy; } ;
struct stat {int dummy; } ;
struct patch {int /*<<< orphan*/  is_binary; int /*<<< orphan*/  old_name; int /*<<< orphan*/ * fragments; int /*<<< orphan*/  old_mode; int /*<<< orphan*/  resultsize; int /*<<< orphan*/  result; } ;
struct image {int dummy; } ;
struct cache_entry {int dummy; } ;
struct apply_state {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int SUBMODULE_PATCH_WITHOUT_INDEX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_fragment_list (int /*<<< orphan*/ *) ; 
 int load_patch_target (struct apply_state*,struct strbuf*,struct cache_entry const*,struct stat*,struct patch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_image (struct image*,char*,size_t,int) ; 
 struct patch* previous_patch (struct apply_state*,struct patch*,int*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 

__attribute__((used)) static int load_preimage(struct apply_state *state,
			 struct image *image,
			 struct patch *patch, struct stat *st,
			 const struct cache_entry *ce)
{
	struct strbuf buf = STRBUF_INIT;
	size_t len;
	char *img;
	struct patch *previous;
	int status;

	previous = previous_patch(state, patch, &status);
	if (status)
		return error(_("path %s has been renamed/deleted"),
			     patch->old_name);
	if (previous) {
		/* We have a patched copy in memory; use that. */
		strbuf_add(&buf, previous->result, previous->resultsize);
	} else {
		status = load_patch_target(state, &buf, ce, st, patch,
					   patch->old_name, patch->old_mode);
		if (status < 0)
			return status;
		else if (status == SUBMODULE_PATCH_WITHOUT_INDEX) {
			/*
			 * There is no way to apply subproject
			 * patch without looking at the index.
			 * NEEDSWORK: shouldn't this be flagged
			 * as an error???
			 */
			free_fragment_list(patch->fragments);
			patch->fragments = NULL;
		} else if (status) {
			return error(_("failed to read %s"), patch->old_name);
		}
	}

	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
	return 0;
}