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
struct pack_backend {int dummy; } ;
struct git_pack_entry {int /*<<< orphan*/  offset; int /*<<< orphan*/  p; } ;
struct git_odb_backend {int dummy; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_packfile_resolve_header (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pack_entry_find (struct git_pack_entry*,struct pack_backend*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int pack_backend__read_header(
	size_t *len_p, git_object_t *type_p,
	struct git_odb_backend *backend, const git_oid *oid)
{
	struct git_pack_entry e;
	int error;

	assert(len_p && type_p && backend && oid);

	if ((error = pack_entry_find(&e, (struct pack_backend *)backend, oid)) < 0)
		return error;

	return git_packfile_resolve_header(len_p, type_p, e.p, e.offset);
}