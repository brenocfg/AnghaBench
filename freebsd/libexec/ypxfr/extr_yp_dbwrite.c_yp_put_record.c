#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* put ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* close ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  DBT ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 int /*<<< orphan*/  R_NOOVERWRITE ; 
 int YP_BADDB ; 
 int YP_FALSE ; 
 int YP_TRUE ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 

int
yp_put_record(DB *dbp, DBT *key, DBT *data, int allow_overwrite)
{
	int rval;

	if ((rval = (dbp->put)(dbp,key,data, allow_overwrite ? 0 :
							R_NOOVERWRITE))) {
		switch (rval) {
		case 1:
			return(YP_FALSE);
			break;
		case -1:
		default:
			(void)(dbp->close)(dbp);
			return(YP_BADDB);
			break;
		}
	}

	return(YP_TRUE);
}