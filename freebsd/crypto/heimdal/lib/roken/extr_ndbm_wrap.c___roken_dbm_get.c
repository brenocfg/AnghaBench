#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ dsize; int /*<<< orphan*/ * dptr; } ;
typedef  TYPE_1__ datum ;
struct TYPE_13__ {scalar_t__ (* c_get ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* seq ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* cursor ) (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  DBT2DATUM (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_4__* cursor ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static datum
dbm_get (DB *db, int flags)
{
    DBT key, value;
    datum datum;
#ifdef HAVE_DB3
    if(cursor == NULL)
	db->cursor(db, NULL, &cursor, 0);
    if(cursor->c_get(cursor, &key, &value, flags) != 0) {
	datum.dptr = NULL;
	datum.dsize = 0;
    } else
	DBT2DATUM(&value, &datum);
#else
    db->seq(db, &key, &value, flags);
    DBT2DATUM(&value, &datum);
#endif
    return datum;
}