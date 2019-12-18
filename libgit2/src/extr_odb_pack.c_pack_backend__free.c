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
struct TYPE_3__ {size_t length; } ;
struct pack_backend {struct pack_backend* pack_folder; TYPE_1__ packs; } ;
struct git_pack_file {int dummy; } ;
typedef  int /*<<< orphan*/  git_odb_backend ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (struct pack_backend*) ; 
 int /*<<< orphan*/  git_mwindow_put_pack (struct git_pack_file*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 
 struct git_pack_file* git_vector_get (TYPE_1__*,size_t) ; 

__attribute__((used)) static void pack_backend__free(git_odb_backend *_backend)
{
	struct pack_backend *backend;
	size_t i;

	assert(_backend);

	backend = (struct pack_backend *)_backend;

	for (i = 0; i < backend->packs.length; ++i) {
		struct git_pack_file *p = git_vector_get(&backend->packs, i);
		git_mwindow_put_pack(p);
	}

	git_vector_free(&backend->packs);
	git__free(backend->pack_folder);
	git__free(backend);
}