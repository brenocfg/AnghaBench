#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_8__ {int (* read_header ) (size_t*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  refresh; } ;
typedef  TYPE_1__ git_odb_backend ;
struct TYPE_11__ {size_t length; } ;
struct TYPE_9__ {TYPE_7__ backends; } ;
typedef  TYPE_2__ git_odb ;
typedef  int /*<<< orphan*/  git_object_t ;
struct TYPE_10__ {TYPE_1__* backend; } ;
typedef  TYPE_3__ backend_internal ;

/* Variables and functions */
#define  GIT_ENOTFOUND 129 
 int /*<<< orphan*/  GIT_OBJECT_INVALID ; 
#define  GIT_PASSTHROUGH 128 
 TYPE_3__* git_vector_get (TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  odb_hardcoded_type (int /*<<< orphan*/  const*) ; 
 int stub1 (size_t*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int odb_read_header_1(
	size_t *len_p, git_object_t *type_p, git_odb *db,
	const git_oid *id, bool only_refreshed)
{
	size_t i;
	git_object_t ht;
	bool passthrough = false;
	int error;

	if (!only_refreshed && (ht = odb_hardcoded_type(id)) != GIT_OBJECT_INVALID) {
		*type_p = ht;
		*len_p = 0;
		return 0;
	}

	for (i = 0; i < db->backends.length; ++i) {
		backend_internal *internal = git_vector_get(&db->backends, i);
		git_odb_backend *b = internal->backend;

		if (only_refreshed && !b->refresh)
			continue;

		if (!b->read_header) {
			passthrough = true;
			continue;
		}

		error = b->read_header(len_p, type_p, b, id);

		switch (error) {
		case GIT_PASSTHROUGH:
			passthrough = true;
			break;
		case GIT_ENOTFOUND:
			break;
		default:
			return error;
		}
	}

	return passthrough ? GIT_PASSTHROUGH : GIT_ENOTFOUND;
}