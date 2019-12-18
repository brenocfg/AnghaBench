#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__** recs; } ;
struct TYPE_7__ {TYPE_2__ xdf2; } ;
typedef  TYPE_3__ xdfenv_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 scalar_t__ line_contains_alnum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lines_contain_alnum(xdfenv_t *xe, int i, int chg)
{
	for (; chg; chg--, i++)
		if (line_contains_alnum(xe->xdf2.recs[i]->ptr,
				xe->xdf2.recs[i]->size))
			return 1;
	return 0;
}