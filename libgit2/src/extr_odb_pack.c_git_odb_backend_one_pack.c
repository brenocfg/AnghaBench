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
struct pack_backend {int /*<<< orphan*/  packs; } ;
struct git_pack_file {int dummy; } ;
typedef  int /*<<< orphan*/  git_odb_backend ;

/* Variables and functions */
 scalar_t__ git_mwindow_get_pack (struct git_pack_file**,char const*) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,struct git_pack_file*) ; 
 scalar_t__ pack_backend__alloc (struct pack_backend**,int) ; 
 int /*<<< orphan*/  pack_backend__free (int /*<<< orphan*/ *) ; 

int git_odb_backend_one_pack(git_odb_backend **backend_out, const char *idx)
{
	struct pack_backend *backend = NULL;
	struct git_pack_file *packfile = NULL;

	if (pack_backend__alloc(&backend, 1) < 0)
		return -1;

	if (git_mwindow_get_pack(&packfile, idx) < 0 ||
		git_vector_insert(&backend->packs, packfile) < 0)
	{
		pack_backend__free((git_odb_backend *)backend);
		return -1;
	}

	*backend_out = (git_odb_backend *)backend;
	return 0;
}