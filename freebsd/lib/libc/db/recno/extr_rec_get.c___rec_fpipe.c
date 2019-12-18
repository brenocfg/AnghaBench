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
typedef  int u_char ;
typedef  scalar_t__ recno_t ;
struct TYPE_8__ {size_t size; int* data; } ;
struct TYPE_10__ {size_t bt_reclen; scalar_t__ bt_nrecs; int /*<<< orphan*/  bt_bval; int /*<<< orphan*/  bt_rfp; TYPE_1__ bt_rdata; } ;
struct TYPE_9__ {int* data; size_t size; } ;
typedef  TYPE_2__ DBT ;
typedef  TYPE_3__ BTREE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  F_SET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int RET_ERROR ; 
 int RET_SPECIAL ; 
 scalar_t__ RET_SUCCESS ; 
 int /*<<< orphan*/  R_EOF ; 
 scalar_t__ __rec_iput (TYPE_3__*,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int* reallocf (int*,size_t) ; 

int
__rec_fpipe(BTREE *t, recno_t top)
{
	DBT data;
	recno_t nrec;
	size_t len;
	int ch;
	u_char *p;

	if (t->bt_rdata.size < t->bt_reclen) {
		t->bt_rdata.data = reallocf(t->bt_rdata.data, t->bt_reclen);
		if (t->bt_rdata.data == NULL)
			return (RET_ERROR);
		t->bt_rdata.size = t->bt_reclen;
	}
	data.data = t->bt_rdata.data;
	data.size = t->bt_reclen;

	for (nrec = t->bt_nrecs; nrec < top;) {
		len = t->bt_reclen;
		for (p = t->bt_rdata.data;; *p++ = ch)
			if ((ch = getc(t->bt_rfp)) == EOF || !--len) {
				if (ch != EOF)
					*p = ch;
				if (len != 0)
					memset(p, t->bt_bval, len);
				if (__rec_iput(t,
				    nrec, &data, 0) != RET_SUCCESS)
					return (RET_ERROR);
				++nrec;
				break;
			}
		if (ch == EOF)
			break;
	}
	if (nrec < top) {
		F_SET(t, R_EOF);
		return (RET_SPECIAL);
	}
	return (RET_SUCCESS);
}