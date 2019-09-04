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
struct TYPE_2__ {int /*<<< orphan*/ * free; int /*<<< orphan*/ * freshen; int /*<<< orphan*/ * writepack; int /*<<< orphan*/ * foreach; int /*<<< orphan*/ * refresh; int /*<<< orphan*/ * exists_prefix; int /*<<< orphan*/ * exists; int /*<<< orphan*/ * read_header; int /*<<< orphan*/ * read_prefix; int /*<<< orphan*/ * read; int /*<<< orphan*/  version; } ;
struct pack_backend {TYPE_1__ parent; int /*<<< orphan*/  packs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct pack_backend*) ; 
 int /*<<< orphan*/  GIT_ODB_BACKEND_VERSION ; 
 struct pack_backend* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (struct pack_backend*) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pack_backend__exists ; 
 int /*<<< orphan*/  pack_backend__exists_prefix ; 
 int /*<<< orphan*/  pack_backend__foreach ; 
 int /*<<< orphan*/  pack_backend__free ; 
 int /*<<< orphan*/  pack_backend__freshen ; 
 int /*<<< orphan*/  pack_backend__read ; 
 int /*<<< orphan*/  pack_backend__read_header ; 
 int /*<<< orphan*/  pack_backend__read_prefix ; 
 int /*<<< orphan*/  pack_backend__refresh ; 
 int /*<<< orphan*/  pack_backend__writepack ; 
 int /*<<< orphan*/  packfile_sort__cb ; 

__attribute__((used)) static int pack_backend__alloc(struct pack_backend **out, size_t initial_size)
{
	struct pack_backend *backend = git__calloc(1, sizeof(struct pack_backend));
	GIT_ERROR_CHECK_ALLOC(backend);

	if (git_vector_init(&backend->packs, initial_size, packfile_sort__cb) < 0) {
		git__free(backend);
		return -1;
	}

	backend->parent.version = GIT_ODB_BACKEND_VERSION;

	backend->parent.read = &pack_backend__read;
	backend->parent.read_prefix = &pack_backend__read_prefix;
	backend->parent.read_header = &pack_backend__read_header;
	backend->parent.exists = &pack_backend__exists;
	backend->parent.exists_prefix = &pack_backend__exists_prefix;
	backend->parent.refresh = &pack_backend__refresh;
	backend->parent.foreach = &pack_backend__foreach;
	backend->parent.writepack = &pack_backend__writepack;
	backend->parent.freshen = &pack_backend__freshen;
	backend->parent.free = &pack_backend__free;

	*out = backend;
	return 0;
}