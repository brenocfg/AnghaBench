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
struct tbl_span {struct tbl_span* next; } ;
struct tbl_node {struct tbl_span* current_span; struct tbl_span* first_span; } ;

/* Variables and functions */

struct tbl_span *
tbl_span(struct tbl_node *tbl)
{
	struct tbl_span	 *span;

	span = tbl->current_span ? tbl->current_span->next
				 : tbl->first_span;
	if (span != NULL)
		tbl->current_span = span;
	return span;
}