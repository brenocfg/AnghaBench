#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* fts_statp; } ;
struct TYPE_7__ {int /*<<< orphan*/  g_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  st_gid; } ;
typedef  TYPE_2__ PLAN ;
typedef  TYPE_3__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
f_group(PLAN *plan, FTSENT *entry)
{
	COMPARE(entry->fts_statp->st_gid, plan->g_data);
}