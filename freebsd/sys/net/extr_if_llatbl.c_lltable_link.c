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
struct lltable {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LLTABLE_LIST_WLOCK () ; 
 int /*<<< orphan*/  LLTABLE_LIST_WUNLOCK () ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct lltable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_lltables ; 
 int /*<<< orphan*/  llt_link ; 

void
lltable_link(struct lltable *llt)
{

	LLTABLE_LIST_WLOCK();
	SLIST_INSERT_HEAD(&V_lltables, llt, llt_link);
	LLTABLE_LIST_WUNLOCK();
}