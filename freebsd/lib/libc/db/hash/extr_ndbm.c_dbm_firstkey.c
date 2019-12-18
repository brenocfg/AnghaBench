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
struct TYPE_9__ {int /*<<< orphan*/  dsize; int /*<<< orphan*/ * dptr; } ;
typedef  TYPE_1__ datum ;
struct TYPE_11__ {int (* seq ) (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ DBM ;

/* Variables and functions */
 int /*<<< orphan*/  R_FIRST ; 
 int stub1 (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

extern datum
dbm_firstkey(DBM *db)
{
	int status;
	datum retkey;
	DBT dbtretkey, dbtretdata;

	status = (db->seq)(db, &dbtretkey, &dbtretdata, R_FIRST);
	if (status)
		dbtretkey.data = NULL;
	retkey.dptr = dbtretkey.data;
	retkey.dsize = dbtretkey.size;
	return (retkey);
}