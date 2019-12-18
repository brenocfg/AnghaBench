#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; } ;
struct git_pack_file {unsigned int num_bad_objects; TYPE_1__ mwf; int /*<<< orphan*/ * bad_object_sha1; } ;
struct git_pack_entry {int /*<<< orphan*/  sha1; struct git_pack_file* p; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_off_t ;

/* Variables and functions */
 size_t GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  assert (struct git_pack_file*) ; 
 scalar_t__ git_oid__cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pack_entry_find_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct git_pack_file*,int /*<<< orphan*/  const*,size_t) ; 
 int packfile_error (char*) ; 
 int packfile_open (struct git_pack_file*) ; 

int git_pack_entry_find(
		struct git_pack_entry *e,
		struct git_pack_file *p,
		const git_oid *short_oid,
		size_t len)
{
	git_off_t offset;
	git_oid found_oid;
	int error;

	assert(p);

	if (len == GIT_OID_HEXSZ && p->num_bad_objects) {
		unsigned i;
		for (i = 0; i < p->num_bad_objects; i++)
			if (git_oid__cmp(short_oid, &p->bad_object_sha1[i]) == 0)
				return packfile_error("bad object found in packfile");
	}

	error = pack_entry_find_offset(&offset, &found_oid, p, short_oid, len);
	if (error < 0)
		return error;

	/* we found a unique entry in the index;
	 * make sure the packfile backing the index
	 * still exists on disk */
	if (p->mwf.fd == -1 && (error = packfile_open(p)) < 0)
		return error;

	e->offset = offset;
	e->p = p;

	git_oid_cpy(&e->sha1, &found_oid);
	return 0;
}