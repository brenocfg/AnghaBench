#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {int (* exists ) (TYPE_1__*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* freshen ) (TYPE_1__*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  refresh; } ;
typedef  TYPE_1__ git_odb_backend ;
struct TYPE_12__ {size_t length; } ;
struct TYPE_10__ {TYPE_8__ backends; } ;
typedef  TYPE_2__ git_odb ;
struct TYPE_11__ {TYPE_1__* backend; } ;
typedef  TYPE_3__ backend_internal ;

/* Variables and functions */
 TYPE_3__* git_vector_get (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int odb_freshen_1(
	git_odb *db,
	const git_oid *id,
	bool only_refreshed)
{
	size_t i;
	bool found = false;

	for (i = 0; i < db->backends.length && !found; ++i) {
		backend_internal *internal = git_vector_get(&db->backends, i);
		git_odb_backend *b = internal->backend;

		if (only_refreshed && !b->refresh)
			continue;

		if (b->freshen != NULL)
			found = !b->freshen(b, id);
		else if (b->exists != NULL)
			found = b->exists(b, id);
	}

	return (int)found;
}