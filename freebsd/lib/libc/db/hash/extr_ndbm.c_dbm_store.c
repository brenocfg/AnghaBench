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
struct TYPE_10__ {int /*<<< orphan*/  dsize; int /*<<< orphan*/  dptr; } ;
typedef  TYPE_1__ datum ;
struct TYPE_12__ {int (* put ) (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ DBM ;

/* Variables and functions */
 int DBM_INSERT ; 
 int /*<<< orphan*/  R_NOOVERWRITE ; 
 int stub1 (TYPE_3__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 

extern int
dbm_store(DBM *db, datum key, datum data, int flags)
{
	DBT dbtkey, dbtdata;

	dbtkey.data = key.dptr;
	dbtkey.size = key.dsize;
	dbtdata.data = data.dptr;
	dbtdata.size = data.dsize;
	return ((db->put)(db, &dbtkey, &dbtdata,
	    (flags == DBM_INSERT) ? R_NOOVERWRITE : 0));
}