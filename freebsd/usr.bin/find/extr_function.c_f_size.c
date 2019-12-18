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
typedef  int off_t ;
struct TYPE_8__ {TYPE_1__* fts_statp; } ;
struct TYPE_7__ {int /*<<< orphan*/  o_data; } ;
struct TYPE_6__ {int st_size; } ;
typedef  TYPE_2__ PLAN ;
typedef  TYPE_3__ FTSENT ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE (int,int /*<<< orphan*/ ) ; 
 int FIND_SIZE ; 
 scalar_t__ divsize ; 

int
f_size(PLAN *plan, FTSENT *entry)
{
	off_t size;

	size = divsize ? (entry->fts_statp->st_size + FIND_SIZE - 1) /
	    FIND_SIZE : entry->fts_statp->st_size;
	COMPARE(size, plan->o_data);
}