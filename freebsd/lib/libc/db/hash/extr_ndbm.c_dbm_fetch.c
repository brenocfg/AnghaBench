#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ dsize; int /*<<< orphan*/ * dptr; } ;
typedef  TYPE_1__ datum ;
struct TYPE_12__ {int (* get ) (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ DBM ;

/* Variables and functions */
 int stub1 (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

extern datum
dbm_fetch(DBM *db, datum key)
{
	datum retdata;
	int status;
	DBT dbtkey, dbtretdata;

	dbtkey.data = key.dptr;
	dbtkey.size = key.dsize;
	status = (db->get)(db, &dbtkey, &dbtretdata, 0);
	if (status) {
		dbtretdata.data = NULL;
		dbtretdata.size = 0;
	}
	retdata.dptr = dbtretdata.data;
	retdata.dsize = dbtretdata.size;
	return (retdata);
}