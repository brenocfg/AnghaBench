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
struct TYPE_6__ {int should_write; int /*<<< orphan*/  file; TYPE_2__* index; } ;
typedef  TYPE_1__ git_indexwriter ;
struct TYPE_7__ {int /*<<< orphan*/  index_file_path; } ;
typedef  TYPE_2__ git_index ;

/* Variables and functions */
 int GIT_ELOCKED ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int /*<<< orphan*/  GIT_FILEBUF_HASH_CONTENTS ; 
 int /*<<< orphan*/  GIT_INDEX_FILE_MODE ; 
 int /*<<< orphan*/  GIT_REFCOUNT_INC (TYPE_2__*) ; 
 int create_index_error (int,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_filebuf_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_indexwriter_init(
	git_indexwriter *writer,
	git_index *index)
{
	int error;

	GIT_REFCOUNT_INC(index);

	writer->index = index;

	if (!index->index_file_path)
		return create_index_error(-1,
			"failed to write index: The index is in-memory only");

	if ((error = git_filebuf_open(
		&writer->file, index->index_file_path, GIT_FILEBUF_HASH_CONTENTS, GIT_INDEX_FILE_MODE)) < 0) {

		if (error == GIT_ELOCKED)
			git_error_set(GIT_ERROR_INDEX, "the index is locked; this might be due to a concurrent or crashed process");

		return error;
	}

	writer->should_write = 1;

	return 0;
}