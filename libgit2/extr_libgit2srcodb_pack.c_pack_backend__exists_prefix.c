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
struct git_pack_entry {int /*<<< orphan*/  sha1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_backend ;

/* Variables and functions */
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pack_entry_find_prefix (struct git_pack_entry*,struct pack_backend*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int pack_backend__exists_prefix(
	git_oid *out, git_odb_backend *backend, const git_oid *short_id, size_t len)
{
	int error;
	struct pack_backend *pb = (struct pack_backend *)backend;
	struct git_pack_entry e = {0};

	error = pack_entry_find_prefix(&e, pb, short_id, len);
	git_oid_cpy(out, &e.sha1);
	return error;
}