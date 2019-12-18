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
struct string_list_item {char* string; struct rerere_id* util; } ;
struct string_list {int dummy; } ;
struct rerere_id {int variant; struct rerere_dir* collection; } ;
struct rerere_dir {int* status; int status_nr; } ;
struct index_state {int dummy; } ;

/* Variables and functions */
 int RR_HAS_POSTIMAGE ; 
 int RR_HAS_PREIMAGE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assign_variant (struct rerere_id*) ; 
 int /*<<< orphan*/  copy_file (char*,char const*,int) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free_rerere_id (struct string_list_item*) ; 
 int /*<<< orphan*/  handle_file (struct index_state*,char const*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ merge (struct index_state*,struct rerere_id*,char const*) ; 
 int /*<<< orphan*/  remove_variant (struct rerere_id*) ; 
 scalar_t__ rerere_autoupdate ; 
 char* rerere_path (struct rerere_id*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,char const*) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static void do_rerere_one_path(struct index_state *istate,
			       struct string_list_item *rr_item,
			       struct string_list *update)
{
	const char *path = rr_item->string;
	struct rerere_id *id = rr_item->util;
	struct rerere_dir *rr_dir = id->collection;
	int variant;

	variant = id->variant;

	/* Has the user resolved it already? */
	if (variant >= 0) {
		if (!handle_file(istate, path, NULL, NULL)) {
			copy_file(rerere_path(id, "postimage"), path, 0666);
			id->collection->status[variant] |= RR_HAS_POSTIMAGE;
			fprintf_ln(stderr, _("Recorded resolution for '%s'."), path);
			free_rerere_id(rr_item);
			rr_item->util = NULL;
			return;
		}
		/*
		 * There may be other variants that can cleanly
		 * replay.  Try them and update the variant number for
		 * this one.
		 */
	}

	/* Does any existing resolution apply cleanly? */
	for (variant = 0; variant < rr_dir->status_nr; variant++) {
		const int both = RR_HAS_PREIMAGE | RR_HAS_POSTIMAGE;
		struct rerere_id vid = *id;

		if ((rr_dir->status[variant] & both) != both)
			continue;

		vid.variant = variant;
		if (merge(istate, &vid, path))
			continue; /* failed to replay */

		/*
		 * If there already is a different variant that applies
		 * cleanly, there is no point maintaining our own variant.
		 */
		if (0 <= id->variant && id->variant != variant)
			remove_variant(id);

		if (rerere_autoupdate)
			string_list_insert(update, path);
		else
			fprintf_ln(stderr,
				   _("Resolved '%s' using previous resolution."),
				   path);
		free_rerere_id(rr_item);
		rr_item->util = NULL;
		return;
	}

	/* None of the existing one applies; we need a new variant */
	assign_variant(id);

	variant = id->variant;
	handle_file(istate, path, NULL, rerere_path(id, "preimage"));
	if (id->collection->status[variant] & RR_HAS_POSTIMAGE) {
		const char *path = rerere_path(id, "postimage");
		if (unlink(path))
			die_errno(_("cannot unlink stray '%s'"), path);
		id->collection->status[variant] &= ~RR_HAS_POSTIMAGE;
	}
	id->collection->status[variant] |= RR_HAS_PREIMAGE;
	fprintf_ln(stderr, _("Recorded preimage for '%s'"), path);
}