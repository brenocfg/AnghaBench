#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {int dummy; } ;
struct aeu_invert_reg_bit {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ATTENTION_PARITY ; 
 TYPE_1__* ecore_int_aeu_translate (struct ecore_hwfn*,struct aeu_invert_reg_bit*) ; 

__attribute__((used)) static bool ecore_int_is_parity_flag(struct ecore_hwfn *p_hwfn,
				     struct aeu_invert_reg_bit *p_bit)
{
	return !!(ecore_int_aeu_translate(p_hwfn, p_bit)->flags &
		  ATTENTION_PARITY);
}