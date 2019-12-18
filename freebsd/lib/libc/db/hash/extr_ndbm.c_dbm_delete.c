#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dsize; int /*<<< orphan*/  dptr; } ;
typedef  TYPE_1__ datum ;
struct TYPE_10__ {int (* del ) (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ DBM ;

/* Variables and functions */
 int stub1 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

extern int
dbm_delete(DBM *db, datum key)
{
	int status;
	DBT dbtkey;

	dbtkey.data = key.dptr;
	dbtkey.size = key.dsize;
	status = (db->del)(db, &dbtkey, 0);
	if (status)
		return (-1);
	else
		return (0);
}