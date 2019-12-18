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
typedef  int /*<<< orphan*/  session_t ;
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_7__ {scalar_t__ (* get ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__* session_db ; 
 scalar_t__ stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static session_t *
find_session(pid_t pid)
{
	DBT key;
	DBT data;
	session_t *ret;

	key.data = &pid;
	key.size = sizeof pid;
	if ((*session_db->get)(session_db, &key, &data, 0) != 0)
		return 0;
	bcopy(data.data, (char *)&ret, sizeof(ret));
	return ret;
}