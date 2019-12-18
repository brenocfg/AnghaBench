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
typedef  int mode_t ;
struct TYPE_8__ {TYPE_1__* fts_statp; } ;
struct TYPE_7__ {int flags; int m_data; } ;
struct TYPE_6__ {int st_mode; } ;
typedef  TYPE_2__ PLAN ;
typedef  TYPE_3__ FTSENT ;

/* Variables and functions */
 int F_ANY ; 
 int F_ATLEAST ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_ISGID ; 
 int S_ISTXT ; 
 int S_ISUID ; 

int
f_perm(PLAN *plan, FTSENT *entry)
{
	mode_t mode;

	mode = entry->fts_statp->st_mode &
	    (S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO);
	if (plan->flags & F_ATLEAST)
		return (plan->m_data | mode) == mode;
	else if (plan->flags & F_ANY)
		return (mode & plan->m_data);
	else
		return mode == plan->m_data;
	/* NOTREACHED */
}