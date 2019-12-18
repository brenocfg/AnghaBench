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
struct tbl_node {scalar_t__ part; int line; int pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_TBLDATA_BLK ; 
 scalar_t__ TBL_PART_CDATA ; 
 scalar_t__ TBL_PART_LAYOUT ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int,char*) ; 

void
tbl_restart(int line, int pos, struct tbl_node *tbl)
{
	if (tbl->part == TBL_PART_CDATA)
		mandoc_msg(MANDOCERR_TBLDATA_BLK, line, pos, "T&");

	tbl->part = TBL_PART_LAYOUT;
	tbl->line = line;
	tbl->pos = pos;
}