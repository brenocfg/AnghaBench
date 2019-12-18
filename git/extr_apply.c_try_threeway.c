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
struct patch {char* new_name; char* old_name; int conflicted_threeway; int /*<<< orphan*/ * threeway_stage; scalar_t__ is_new; int /*<<< orphan*/  old_mode; int /*<<< orphan*/  old_oid_prefix; int /*<<< orphan*/  new_mode; scalar_t__ is_delete; } ;
struct object_id {int dummy; } ;
struct image {char* buf; int /*<<< orphan*/  len; } ;
struct cache_entry {int dummy; } ;
struct apply_state {scalar_t__ apply_verbosity; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 scalar_t__ apply_fragments (struct apply_state*,struct image*,struct patch*) ; 
 int /*<<< orphan*/  blob_type ; 
 int /*<<< orphan*/  clear_image (struct image*) ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_oid (int /*<<< orphan*/ ,struct object_id*) ; 
 scalar_t__ load_current (struct apply_state*,struct image*,struct patch*) ; 
 scalar_t__ load_preimage (struct apply_state*,struct image*,struct patch*,struct stat*,struct cache_entry const*) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  prepare_image (struct image*,char*,size_t,int) ; 
 scalar_t__ read_blob_object (struct strbuf*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strbuf_detach (struct strbuf*,size_t*) ; 
 int three_way_merge (struct apply_state*,struct image*,char*,struct object_id*,struct object_id*,struct object_id*) ; 
 scalar_t__ verbosity_silent ; 
 int /*<<< orphan*/  write_object_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int try_threeway(struct apply_state *state,
			struct image *image,
			struct patch *patch,
			struct stat *st,
			const struct cache_entry *ce)
{
	struct object_id pre_oid, post_oid, our_oid;
	struct strbuf buf = STRBUF_INIT;
	size_t len;
	int status;
	char *img;
	struct image tmp_image;

	/* No point falling back to 3-way merge in these cases */
	if (patch->is_delete ||
	    S_ISGITLINK(patch->old_mode) || S_ISGITLINK(patch->new_mode))
		return -1;

	/* Preimage the patch was prepared for */
	if (patch->is_new)
		write_object_file("", 0, blob_type, &pre_oid);
	else if (get_oid(patch->old_oid_prefix, &pre_oid) ||
		 read_blob_object(&buf, &pre_oid, patch->old_mode))
		return error(_("repository lacks the necessary blob to fall back on 3-way merge."));

	if (state->apply_verbosity > verbosity_silent)
		fprintf(stderr, _("Falling back to three-way merge...\n"));

	img = strbuf_detach(&buf, &len);
	prepare_image(&tmp_image, img, len, 1);
	/* Apply the patch to get the post image */
	if (apply_fragments(state, &tmp_image, patch) < 0) {
		clear_image(&tmp_image);
		return -1;
	}
	/* post_oid is theirs */
	write_object_file(tmp_image.buf, tmp_image.len, blob_type, &post_oid);
	clear_image(&tmp_image);

	/* our_oid is ours */
	if (patch->is_new) {
		if (load_current(state, &tmp_image, patch))
			return error(_("cannot read the current contents of '%s'"),
				     patch->new_name);
	} else {
		if (load_preimage(state, &tmp_image, patch, st, ce))
			return error(_("cannot read the current contents of '%s'"),
				     patch->old_name);
	}
	write_object_file(tmp_image.buf, tmp_image.len, blob_type, &our_oid);
	clear_image(&tmp_image);

	/* in-core three-way merge between post and our using pre as base */
	status = three_way_merge(state, image, patch->new_name,
				 &pre_oid, &our_oid, &post_oid);
	if (status < 0) {
		if (state->apply_verbosity > verbosity_silent)
			fprintf(stderr,
				_("Failed to fall back on three-way merge...\n"));
		return status;
	}

	if (status) {
		patch->conflicted_threeway = 1;
		if (patch->is_new)
			oidclr(&patch->threeway_stage[0]);
		else
			oidcpy(&patch->threeway_stage[0], &pre_oid);
		oidcpy(&patch->threeway_stage[1], &our_oid);
		oidcpy(&patch->threeway_stage[2], &post_oid);
		if (state->apply_verbosity > verbosity_silent)
			fprintf(stderr,
				_("Applied patch to '%s' with conflicts.\n"),
				patch->new_name);
	} else {
		if (state->apply_verbosity > verbosity_silent)
			fprintf(stderr,
				_("Applied patch to '%s' cleanly.\n"),
				patch->new_name);
	}
	return 0;
}