#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_3__ {size_t bank; scalar_t__ offset; } ;
typedef  TYPE_1__ BANK_PTR ;

/* Variables and functions */
 scalar_t__* bank_data_ptrs ; 
 int /*<<< orphan*/  initrand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptr_div_reg ; 
 scalar_t__ script_ptr ; 
 size_t script_ptr_bank ; 
 scalar_t__ script_start_ptr ; 

void ScriptStart(BANK_PTR *events_ptr)
{
  UBYTE rnd;
  script_ptr_bank = events_ptr->bank;
  script_ptr = ((UWORD)bank_data_ptrs[script_ptr_bank]) + events_ptr->offset;

  rnd = *(ptr_div_reg);
  initrand(rnd);

  script_start_ptr = script_ptr;
}