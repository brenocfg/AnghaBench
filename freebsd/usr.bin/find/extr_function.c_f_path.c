#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fts_path; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  c_data; } ;
typedef  TYPE_1__ PLAN ;
typedef  TYPE_2__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  FNM_CASEFOLD ; 
 int F_IGNCASE ; 
 int /*<<< orphan*/  fnmatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
f_path(PLAN *plan, FTSENT *entry)
{
	return !fnmatch(plan->c_data, entry->fts_path,
	    plan->flags & F_IGNCASE ? FNM_CASEFOLD : 0);
}