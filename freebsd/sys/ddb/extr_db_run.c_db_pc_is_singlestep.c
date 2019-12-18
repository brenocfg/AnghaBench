#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ db_addr_t ;
struct TYPE_4__ {scalar_t__ address; } ;
struct TYPE_3__ {scalar_t__ address; } ;

/* Variables and functions */
 TYPE_2__* db_not_taken_bkpt ; 
 TYPE_1__* db_taken_bkpt ; 

__attribute__((used)) static bool
db_pc_is_singlestep(db_addr_t pc)
{
#ifdef SOFTWARE_SSTEP
	if ((db_not_taken_bkpt != 0 && pc == db_not_taken_bkpt->address)
	    || (db_taken_bkpt != 0 && pc == db_taken_bkpt->address))
		return (true);
#endif
	return (false);
}