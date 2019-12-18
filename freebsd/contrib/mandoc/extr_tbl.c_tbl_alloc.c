#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char tab; char decimal; } ;
struct tbl_node {int line; int pos; TYPE_1__ opts; int /*<<< orphan*/  part; struct tbl_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  TBL_PART_OPTS ; 
 struct tbl_node* mandoc_calloc (int,int) ; 

struct tbl_node *
tbl_alloc(int pos, int line, struct tbl_node *last_tbl)
{
	struct tbl_node	*tbl;

	tbl = mandoc_calloc(1, sizeof(*tbl));
	if (last_tbl != NULL)
		last_tbl->next = tbl;
	tbl->line = line;
	tbl->pos = pos;
	tbl->part = TBL_PART_OPTS;
	tbl->opts.tab = '\t';
	tbl->opts.decimal = '.';
	return tbl;
}