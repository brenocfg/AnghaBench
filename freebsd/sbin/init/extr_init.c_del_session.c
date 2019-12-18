#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  se_process; } ;
typedef  TYPE_1__ session_t ;
struct TYPE_9__ {scalar_t__ (* del ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  emergency (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_3__* session_db ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
del_session(session_t *sp)
{
	DBT key;

	key.data = &sp->se_process;
	key.size = sizeof sp->se_process;

	if ((*session_db->del)(session_db, &key, 0))
		emergency("delete %d: %s", sp->se_process, strerror(errno));
}