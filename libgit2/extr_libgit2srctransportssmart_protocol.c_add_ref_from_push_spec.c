#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dst; } ;
struct TYPE_11__ {TYPE_1__ refspec; int /*<<< orphan*/  loid; } ;
typedef  TYPE_3__ push_spec ;
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;
struct TYPE_12__ {TYPE_2__ head; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ git_pkt_ref ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_4__*) ; 
 int /*<<< orphan*/  GIT_PKT_REF ; 
 TYPE_4__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pkt_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static int add_ref_from_push_spec(git_vector *refs, push_spec *push_spec)
{
	git_pkt_ref *added = git__calloc(1, sizeof(git_pkt_ref));
	GIT_ERROR_CHECK_ALLOC(added);

	added->type = GIT_PKT_REF;
	git_oid_cpy(&added->head.oid, &push_spec->loid);
	added->head.name = git__strdup(push_spec->refspec.dst);

	if (!added->head.name ||
		git_vector_insert(refs, added) < 0) {
		git_pkt_free((git_pkt *)added);
		return -1;
	}

	return 0;
}