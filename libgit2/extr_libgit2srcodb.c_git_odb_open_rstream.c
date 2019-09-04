#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_stream ;
struct TYPE_8__ {int (* readstream ) (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_1__ git_odb_backend ;
struct TYPE_11__ {size_t length; } ;
struct TYPE_9__ {TYPE_6__ backends; } ;
typedef  TYPE_2__ git_odb ;
typedef  int /*<<< orphan*/  git_object_t ;
struct TYPE_10__ {TYPE_1__* backend; } ;
typedef  TYPE_3__ backend_internal ;

/* Variables and functions */
 int GIT_ERROR ; 
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  assert (int) ; 
 int git_odb__error_unsupported_in_backend (char*) ; 
 TYPE_3__* git_vector_get (TYPE_6__*,size_t) ; 
 int stub1 (int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 

int git_odb_open_rstream(
	git_odb_stream **stream,
	size_t *len,
	git_object_t *type,
	git_odb *db,
	const git_oid *oid)
{
	size_t i, reads = 0;
	int error = GIT_ERROR;

	assert(stream && db);

	for (i = 0; i < db->backends.length && error < 0; ++i) {
		backend_internal *internal = git_vector_get(&db->backends, i);
		git_odb_backend *b = internal->backend;

		if (b->readstream != NULL) {
			++reads;
			error = b->readstream(stream, len, type, b, oid);
		}
	}

	if (error == GIT_PASSTHROUGH)
		error = 0;
	if (error < 0 && !reads)
		error = git_odb__error_unsupported_in_backend("read object streamed");

	return error;
}