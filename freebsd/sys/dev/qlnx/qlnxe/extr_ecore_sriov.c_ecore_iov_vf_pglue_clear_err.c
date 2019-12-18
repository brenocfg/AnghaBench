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
typedef  int u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 scalar_t__ PGLUE_B_REG_WAS_ERROR_VF_31_0_CLR ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int) ; 

__attribute__((used)) static void ecore_iov_vf_pglue_clear_err(struct ecore_hwfn      *p_hwfn,
					 struct ecore_ptt	*p_ptt,
					 u8			abs_vfid)
{
	ecore_wr(p_hwfn, p_ptt,
		 PGLUE_B_REG_WAS_ERROR_VF_31_0_CLR + (abs_vfid >> 5) * 4,
		 1 << (abs_vfid & 0x1f));
}