#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yplastbuf ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;
struct TYPE_14__ {char* data; unsigned int size; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 int ERR_ACCESS ; 
 int ERR_DBASE ; 
 int ERR_KEY ; 
 int /*<<< orphan*/  O_RDWR ; 
#define  YPOP_CHANGE 131 
#define  YPOP_DELETE 130 
#define  YPOP_INSERT 129 
#define  YPOP_STORE 128 
 int YP_TRUE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 void* strlen (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int yp_del_record (TYPE_2__*,TYPE_1__*) ; 
 int yp_domake (char*,char*) ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 int yp_get_record (char*,char*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* yp_open_db_rw (char*,char*,int /*<<< orphan*/ ) ; 
 int yp_put_record (TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ; 

int
ypmap_update(char *netname, char *map, unsigned int op, unsigned int keylen,
    char *keyval, unsigned int datlen, char *datval)
{
	DB *dbp;
	DBT key = { NULL, 0 }, data = { NULL, 0 };
	char *yp_last = "YP_LAST_MODIFIED";
	char yplastbuf[32];
	char *domptr;
	int rval = 0;

	if ((domptr = strchr(netname, '@')) == NULL)
		return(ERR_ACCESS);
	domptr++;


	dbp = yp_open_db_rw(domptr, map, O_RDWR);
	if (dbp == NULL)
		return(ERR_DBASE);

	key.data = keyval;
	key.size = keylen;
	data.data = datval;
	data.size = datlen;

	switch (op) {
	case YPOP_DELETE: /* delete this entry */
		rval = yp_del_record(dbp, &key);
		if (rval == YP_TRUE)
			rval = 0;
		break;
	case YPOP_INSERT: /* add, do not change */
		rval = yp_put_record(dbp, &key, &data, 0);
		if (rval == YP_TRUE)
			rval = 0;
		break;
	case YPOP_STORE: /* add, or change */
		rval = yp_put_record(dbp, &key, &data, 1);
		if (rval == YP_TRUE)
			rval = 0;
		break;
	case YPOP_CHANGE: /* change, do not add */
		if (yp_get_record(domptr, map, &key, &data, 0) != YP_TRUE) {
			rval = ERR_KEY;
			break;
		}
		rval = yp_put_record(dbp, &key, &data, 1);
		if (rval == YP_TRUE)
			rval = 0;
		break;
	default:
		yp_error("unknown update command: (%d)", op);
	}

	if (rval) {
		(void)(dbp->close)(dbp);
		return(rval);
	}

	snprintf(yplastbuf, sizeof(yplastbuf), "%jd", (intmax_t)time(NULL));
	key.data = yp_last;
	key.size = strlen(yp_last);
	data.data = (char *)&yplastbuf;
	data.size = strlen(yplastbuf);
	if (yp_put_record(dbp, &key, &data, 1) != YP_TRUE) {
		yp_error("failed to update timestamp in %s/%s", domptr, map);
		(void)(dbp->close)(dbp);
		return(ERR_DBASE);
	}

	(void)(dbp->close)(dbp);
	return(yp_domake(map, domptr));
}