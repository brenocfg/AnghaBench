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
struct TYPE_8__ {scalar_t__ fts_info; TYPE_1__* fts_statp; } ;
struct TYPE_7__ {int m_data; } ;
struct TYPE_6__ {int st_mode; } ;
typedef  TYPE_2__ PLAN ;
typedef  TYPE_3__ FTSENT ;

/* Variables and functions */
 scalar_t__ FTS_D ; 
 scalar_t__ FTS_DC ; 
 scalar_t__ FTS_DNR ; 
 scalar_t__ FTS_DOT ; 
 scalar_t__ FTS_DP ; 
 int S_IFDIR ; 
 int S_IFMT ; 

int
f_type(PLAN *plan, FTSENT *entry)
{
	if (plan->m_data == S_IFDIR)
		return (entry->fts_info == FTS_D || entry->fts_info == FTS_DC ||
		    entry->fts_info == FTS_DNR || entry->fts_info == FTS_DOT ||
		    entry->fts_info == FTS_DP);
	else
		return (entry->fts_statp->st_mode & S_IFMT) == plan->m_data;
}