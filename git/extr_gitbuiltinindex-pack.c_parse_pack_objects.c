#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct ofs_delta_entry {int obj_no; int /*<<< orphan*/  offset; } ;
struct object_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  offset; } ;
struct object_entry {scalar_t__ real_type; scalar_t__ type; TYPE_1__ idx; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int obj_no; int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  rawsz; int /*<<< orphan*/  (* final_fn ) (unsigned char*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ OBJ_BAD ; 
 scalar_t__ OBJ_OFS_DELTA ; 
 scalar_t__ OBJ_REF_DELTA ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  consumed_bytes ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush () ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ from_stdin ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  hasheq (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  input_ctx ; 
 int /*<<< orphan*/  input_fd ; 
 scalar_t__ input_len ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_objects ; 
 int /*<<< orphan*/  nr_ofs_deltas ; 
 int nr_ref_deltas ; 
 struct object_entry* objects ; 
 struct ofs_delta_entry* ofs_deltas ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  progress ; 
 TYPE_3__* ref_deltas ; 
 int /*<<< orphan*/  ref_deltas_alloc ; 
 int /*<<< orphan*/  sha1_object (void*,struct object_entry*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_progress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stop_progress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* the_hash_algo ; 
 void* unpack_raw_entry (struct object_entry*,int /*<<< orphan*/ *,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void parse_pack_objects(unsigned char *hash)
{
	int i, nr_delays = 0;
	struct ofs_delta_entry *ofs_delta = ofs_deltas;
	struct object_id ref_delta_oid;
	struct stat st;

	if (verbose)
		progress = start_progress(
				from_stdin ? _("Receiving objects") : _("Indexing objects"),
				nr_objects);
	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];
		void *data = unpack_raw_entry(obj, &ofs_delta->offset,
					      &ref_delta_oid,
					      &obj->idx.oid);
		obj->real_type = obj->type;
		if (obj->type == OBJ_OFS_DELTA) {
			nr_ofs_deltas++;
			ofs_delta->obj_no = i;
			ofs_delta++;
		} else if (obj->type == OBJ_REF_DELTA) {
			ALLOC_GROW(ref_deltas, nr_ref_deltas + 1, ref_deltas_alloc);
			oidcpy(&ref_deltas[nr_ref_deltas].oid, &ref_delta_oid);
			ref_deltas[nr_ref_deltas].obj_no = i;
			nr_ref_deltas++;
		} else if (!data) {
			/* large blobs, check later */
			obj->real_type = OBJ_BAD;
			nr_delays++;
		} else
			sha1_object(data, NULL, obj->size, obj->type,
				    &obj->idx.oid);
		free(data);
		display_progress(progress, i+1);
	}
	objects[i].idx.offset = consumed_bytes;
	stop_progress(&progress);

	/* Check pack integrity */
	flush();
	the_hash_algo->final_fn(hash, &input_ctx);
	if (!hasheq(fill(the_hash_algo->rawsz), hash))
		die(_("pack is corrupted (SHA1 mismatch)"));
	use(the_hash_algo->rawsz);

	/* If input_fd is a file, we should have reached its end now. */
	if (fstat(input_fd, &st))
		die_errno(_("cannot fstat packfile"));
	if (S_ISREG(st.st_mode) &&
			lseek(input_fd, 0, SEEK_CUR) - input_len != st.st_size)
		die(_("pack has junk at the end"));

	for (i = 0; i < nr_objects; i++) {
		struct object_entry *obj = &objects[i];
		if (obj->real_type != OBJ_BAD)
			continue;
		obj->real_type = obj->type;
		sha1_object(NULL, obj, obj->size, obj->type,
			    &obj->idx.oid);
		nr_delays--;
	}
	if (nr_delays)
		die(_("confusion beyond insanity in parse_pack_objects()"));
}