#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* db; } ;
typedef  TYPE_1__ git_reflog ;
struct TYPE_7__ {TYPE_3__* backend; } ;
typedef  TYPE_2__ git_refdb ;
struct TYPE_8__ {int (* reflog_write ) (TYPE_3__*,TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_3__*,TYPE_1__*) ; 

int git_reflog_write(git_reflog *reflog)
{
	git_refdb *db;

	assert(reflog && reflog->db);

	db = reflog->db;
	return db->backend->reflog_write(db->backend, reflog);
}