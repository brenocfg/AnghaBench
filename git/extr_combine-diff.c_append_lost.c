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
struct TYPE_2__ {int /*<<< orphan*/  len; struct lline* lost_tail; struct lline* lost_head; } ;
struct sline {TYPE_1__ plost; } ;
struct lline {int len; unsigned long parent_map; struct lline* next; struct lline* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct lline*,char const*,char const*,int) ; 

__attribute__((used)) static void append_lost(struct sline *sline, int n, const char *line, int len)
{
	struct lline *lline;
	unsigned long this_mask = (1UL<<n);
	if (line[len-1] == '\n')
		len--;

	FLEX_ALLOC_MEM(lline, line, line, len);
	lline->len = len;
	lline->next = NULL;
	lline->prev = sline->plost.lost_tail;
	if (lline->prev)
		lline->prev->next = lline;
	else
		sline->plost.lost_head = lline;
	sline->plost.lost_tail = lline;
	sline->plost.len++;
	lline->parent_map = this_mask;
}