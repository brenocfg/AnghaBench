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
struct TYPE_11__ {int (* put ) (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {char* data; int size; } ;
struct TYPE_9__ {TYPE_4__* db; } ;
struct TYPE_8__ {TYPE_2__* ep; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ EXF ;
typedef  TYPE_3__ DBT ;

/* Variables and functions */
 int stub1 (TYPE_4__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 

int
db_rset(
	SCR *sp,
	recno_t lno,
	char *p,
	size_t len)
{
	DBT data, key;
	EXF *ep = sp->ep;

	/* Update file. */
	key.data = &lno;
	key.size = sizeof(lno);
	data.data = p;
	data.size = len;
	return ep->db->put(ep->db, &key, &data, 0);
}