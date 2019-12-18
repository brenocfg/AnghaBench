#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pack_backend {int dummy; } ;
struct git_pack_entry {int /*<<< orphan*/  offset; int /*<<< orphan*/  p; } ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/  type; void* data; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ git_rawobj ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int git_packfile_unpack (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pack_entry_find (struct git_pack_entry*,struct pack_backend*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int pack_backend__read(
	void **buffer_p, size_t *len_p, git_object_t *type_p,
	git_odb_backend *backend, const git_oid *oid)
{
	struct git_pack_entry e;
	git_rawobj raw = {NULL};
	int error;

	if ((error = pack_entry_find(&e, (struct pack_backend *)backend, oid)) < 0 ||
		(error = git_packfile_unpack(&raw, e.p, &e.offset)) < 0)
		return error;

	*buffer_p = raw.data;
	*len_p = raw.len;
	*type_p = raw.type;

	return 0;
}