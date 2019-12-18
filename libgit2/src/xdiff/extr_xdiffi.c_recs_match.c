#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ ha; int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ xrecord_t ;

/* Variables and functions */
 scalar_t__ xdl_recmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int recs_match(xrecord_t *rec1, xrecord_t *rec2, long flags)
{
	return (rec1->ha == rec2->ha &&
		xdl_recmatch(rec1->ptr, rec1->size,
			     rec2->ptr, rec2->size,
			     flags));
}