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
struct pack_backend {struct git_pack_file* last_found; } ;
struct git_pack_file {int dummy; } ;
struct git_pack_entry {int dummy; } ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int git_odb__error_notfound (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_pack_entry_find (struct git_pack_entry*,struct git_pack_file*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_entry_find_inner (struct git_pack_entry*,struct pack_backend*,int /*<<< orphan*/  const*,struct git_pack_file*) ; 

__attribute__((used)) static int pack_entry_find(struct git_pack_entry *e, struct pack_backend *backend, const git_oid *oid)
{
	struct git_pack_file *last_found = backend->last_found;

	if (backend->last_found &&
		git_pack_entry_find(e, backend->last_found, oid, GIT_OID_HEXSZ) == 0)
		return 0;

	if (!pack_entry_find_inner(e, backend, oid, last_found))
		return 0;

	return git_odb__error_notfound(
		"failed to find pack entry", oid, GIT_OID_HEXSZ);
}