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
struct tbl_span {int line; struct tbl_span* next; struct tbl_span* prev; struct tbl_row* layout; int /*<<< orphan*/ * opts; } ;
struct tbl_row {int dummy; } ;
struct tbl_node {struct tbl_span* last_span; int /*<<< orphan*/ * current_span; struct tbl_span* first_span; int /*<<< orphan*/  opts; } ;

/* Variables and functions */
 struct tbl_span* mandoc_calloc (int,int) ; 

__attribute__((used)) static struct tbl_span *
newspan(struct tbl_node *tbl, int line, struct tbl_row *rp)
{
	struct tbl_span	*dp;

	dp = mandoc_calloc(1, sizeof(*dp));
	dp->line = line;
	dp->opts = &tbl->opts;
	dp->layout = rp;
	dp->prev = tbl->last_span;

	if (dp->prev == NULL) {
		tbl->first_span = dp;
		tbl->current_span = NULL;
	} else
		dp->prev->next = dp;
	tbl->last_span = dp;

	return dp;
}