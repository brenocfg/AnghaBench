#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tbl_span {struct tbl_span* next; int /*<<< orphan*/ * first; } ;
struct tbl_node {scalar_t__ part; int /*<<< orphan*/  pos; int /*<<< orphan*/  line; struct tbl_span* first_span; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_BLK_NOEND ; 
 int /*<<< orphan*/  MANDOCERR_TBLDATA_BLK ; 
 int /*<<< orphan*/  MANDOCERR_TBLDATA_NONE ; 
 scalar_t__ TBL_PART_CDATA ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int
tbl_end(struct tbl_node *tbl, int still_open)
{
	struct tbl_span *sp;

	if (still_open)
		mandoc_msg(MANDOCERR_BLK_NOEND, tbl->line, tbl->pos, "TS");
	else if (tbl->part == TBL_PART_CDATA)
		mandoc_msg(MANDOCERR_TBLDATA_BLK, tbl->line, tbl->pos, "TE");

	sp = tbl->first_span;
	while (sp != NULL && sp->first == NULL)
		sp = sp->next;
	if (sp == NULL) {
		mandoc_msg(MANDOCERR_TBLDATA_NONE, tbl->line, tbl->pos, NULL);
		return 0;
	}
	return 1;
}