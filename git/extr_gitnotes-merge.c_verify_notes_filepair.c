#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct diff_filepair {int status; TYPE_2__* one; TYPE_1__* two; } ;
struct TYPE_4__ {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
#define  DIFF_STATUS_ADDED 130 
#define  DIFF_STATUS_DELETED 129 
#define  DIFF_STATUS_MODIFIED 128 
 int /*<<< orphan*/  assert (int) ; 
 int is_null_oid (int /*<<< orphan*/ *) ; 
 int path_to_oid (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int verify_notes_filepair(struct diff_filepair *p, struct object_id *oid)
{
	switch (p->status) {
	case DIFF_STATUS_MODIFIED:
		assert(p->one->mode == p->two->mode);
		assert(!is_null_oid(&p->one->oid));
		assert(!is_null_oid(&p->two->oid));
		break;
	case DIFF_STATUS_ADDED:
		assert(is_null_oid(&p->one->oid));
		break;
	case DIFF_STATUS_DELETED:
		assert(is_null_oid(&p->two->oid));
		break;
	default:
		return -1;
	}
	assert(!strcmp(p->one->path, p->two->path));
	return path_to_oid(p->one->path, oid);
}