#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char recno_t ;
typedef  int /*<<< orphan*/  lno ;
struct TYPE_11__ {int (* get ) (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {char* data; int size; } ;
struct TYPE_9__ {TYPE_4__* db; } ;
struct TYPE_8__ {TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXF ;
typedef  TYPE_3__ DBT ;

/* Variables and functions */
 int stub1 (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

int
db_rget(
	SCR *sp,
	recno_t lno,				/* Line number. */
	char **pp,				/* Pointer store. */
	size_t *lenp)				/* Length store. */
{
	DBT data, key;
	EXF *ep = sp->ep;
	int rval;

	/* Get the line from the underlying database. */
	key.data = &lno;
	key.size = sizeof(lno);
	if ((rval = ep->db->get(ep->db, &key, &data, 0)) == 0)
	{
		*lenp = data.size;
		*pp = data.data;
	}

	return (rval);
}