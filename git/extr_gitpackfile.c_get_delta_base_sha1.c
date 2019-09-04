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
struct revindex_entry {int /*<<< orphan*/  nr; } ;
struct packed_git {int dummy; } ;
struct pack_window {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_OFS_DELTA ; 
 int OBJ_REF_DELTA ; 
 struct revindex_entry* find_pack_revindex (struct packed_git*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_delta_base (struct packed_git*,struct pack_window**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 unsigned char const* nth_packed_object_sha1 (struct packed_git*,int /*<<< orphan*/ ) ; 
 unsigned char* use_pack (struct packed_git*,struct pack_window**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const unsigned char *get_delta_base_sha1(struct packed_git *p,
						struct pack_window **w_curs,
						off_t curpos,
						enum object_type type,
						off_t delta_obj_offset)
{
	if (type == OBJ_REF_DELTA) {
		unsigned char *base = use_pack(p, w_curs, curpos, NULL);
		return base;
	} else if (type == OBJ_OFS_DELTA) {
		struct revindex_entry *revidx;
		off_t base_offset = get_delta_base(p, w_curs, &curpos,
						   type, delta_obj_offset);

		if (!base_offset)
			return NULL;

		revidx = find_pack_revindex(p, base_offset);
		if (!revidx)
			return NULL;

		return nth_packed_object_sha1(p, revidx->nr);
	} else
		return NULL;
}