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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ recno_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_8__ {size_t size; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {size_t bt_reclen; scalar_t__ bt_nrecs; scalar_t__ bt_cmap; int /*<<< orphan*/  bt_bval; TYPE_1__ bt_rdata; scalar_t__ bt_emap; } ;
struct TYPE_9__ {size_t size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 scalar_t__ RET_SUCCESS ; 
 int /*<<< orphan*/  R_EOF ; 
 scalar_t__ __rec_iput (TYPE_3__*,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * reallocf (int /*<<< orphan*/ *,size_t) ; 

int
__rec_fmap(BTREE *t, recno_t top)
{
	DBT data;
	recno_t nrec;
	u_char *sp, *ep, *p;
	size_t len;

	if (t->bt_rdata.size < t->bt_reclen) {
		t->bt_rdata.data = reallocf(t->bt_rdata.data, t->bt_reclen);
		if (t->bt_rdata.data == NULL)
			return (RET_ERROR);
		t->bt_rdata.size = t->bt_reclen;
	}
	data.data = t->bt_rdata.data;
	data.size = t->bt_reclen;

	sp = (u_char *)t->bt_cmap;
	ep = (u_char *)t->bt_emap;
	for (nrec = t->bt_nrecs; nrec < top; ++nrec) {
		if (sp >= ep) {
			F_SET(t, R_EOF);
			return (RET_SPECIAL);
		}
		len = t->bt_reclen;
		for (p = t->bt_rdata.data;
		    sp < ep && len > 0; *p++ = *sp++, --len);
		if (len != 0)
			memset(p, t->bt_bval, len);
		if (__rec_iput(t, nrec, &data, 0) != RET_SUCCESS)
			return (RET_ERROR);
	}
	t->bt_cmap = (caddr_t)sp;
	return (RET_SUCCESS);
}