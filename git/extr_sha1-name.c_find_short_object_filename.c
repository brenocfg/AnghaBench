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
struct oid_array {int nr; struct object_id* oid; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct object_directory {struct object_directory* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  hash; } ;
struct disambiguate_state {TYPE_3__ bin_pfx; int /*<<< orphan*/  len; int /*<<< orphan*/  ambiguous; TYPE_2__* repo; } ;
struct TYPE_6__ {TYPE_1__* objects; } ;
struct TYPE_5__ {struct object_directory* odb; } ;

/* Variables and functions */
 int /*<<< orphan*/  match_sha (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct oid_array* odb_loose_cache (struct object_directory*,TYPE_3__*) ; 
 int oid_array_lookup (struct oid_array*,TYPE_3__*) ; 
 int /*<<< orphan*/  update_candidates (struct disambiguate_state*,struct object_id const*) ; 

__attribute__((used)) static void find_short_object_filename(struct disambiguate_state *ds)
{
	struct object_directory *odb;

	for (odb = ds->repo->objects->odb; odb && !ds->ambiguous; odb = odb->next) {
		int pos;
		struct oid_array *loose_objects;

		loose_objects = odb_loose_cache(odb, &ds->bin_pfx);
		pos = oid_array_lookup(loose_objects, &ds->bin_pfx);
		if (pos < 0)
			pos = -1 - pos;
		while (!ds->ambiguous && pos < loose_objects->nr) {
			const struct object_id *oid;
			oid = loose_objects->oid + pos;
			if (!match_sha(ds->len, ds->bin_pfx.hash, oid->hash))
				break;
			update_candidates(ds, oid);
			pos++;
		}
	}
}