#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  read; } ;
struct TYPE_7__ {int /*<<< orphan*/ * index; int /*<<< orphan*/ * repo; TYPE_1__ reader; } ;
typedef  TYPE_2__ index_reader ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reader ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_reader_read ; 

int git_reader_for_index(
	git_reader **out,
	git_repository *repo,
	git_index *index)
{
	index_reader *reader;
	int error;

	assert(out && repo);

	reader = git__calloc(1, sizeof(index_reader));
	GIT_ERROR_CHECK_ALLOC(reader);

	reader->reader.read = index_reader_read;
	reader->repo = repo;

	if (index) {
		reader->index = index;
	} else if ((error = git_repository_index__weakptr(&reader->index, repo)) < 0) {
		git__free(reader);
		return error;
	}

	*out = (git_reader *)reader;
	return 0;
}