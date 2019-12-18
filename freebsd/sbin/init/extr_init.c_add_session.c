#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* se_process; } ;
typedef  TYPE_1__ session_t ;
struct TYPE_11__ {scalar_t__ (* put ) (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int size; TYPE_1__** data; } ;
typedef  TYPE_2__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  emergency (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_3__* session_db ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_session(session_t *sp)
{
	DBT key;
	DBT data;

	key.data = &sp->se_process;
	key.size = sizeof sp->se_process;
	data.data = &sp;
	data.size = sizeof sp;

	if ((*session_db->put)(session_db, &key, &data, 0))
		emergency("insert %d: %s", sp->se_process, strerror(errno));
}