#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; int size; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int YP_TRUE ; 
 int /*<<< orphan*/  dbp ; 
 int yp_errno ; 
 int yp_put_record (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

int
ypxfr_foreach(int status, char *key, int keylen, char *val, int vallen,
    char *data)
{
	DBT dbkey, dbval;

	if (status != YP_TRUE)
		return (status);

	/*
	 * XXX Do not attempt to write zero-length keys or
	 * data into a Berkeley DB hash database. It causes a
	 * strange failure mode where sequential searches get
	 * caught in an infinite loop.
	 */
	if (keylen) {
		dbkey.data = key;
		dbkey.size = keylen;
	} else {
		dbkey.data = "";
		dbkey.size = 1;
	}
	if (vallen) {
		dbval.data = val;
		dbval.size = vallen;
	} else {
		dbval.data = "";
		dbval.size = 1;
	}

	if (yp_put_record(dbp, &dbkey, &dbval, 0) != YP_TRUE)
		return(yp_errno);

	return (0);
}