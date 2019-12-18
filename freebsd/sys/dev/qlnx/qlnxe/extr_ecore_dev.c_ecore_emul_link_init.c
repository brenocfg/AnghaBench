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
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;

/* Variables and functions */
 scalar_t__ ECORE_IS_AH (int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_IS_E5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_emul_link_init_ah_e5 (struct ecore_hwfn*,struct ecore_ptt*) ; 
 int /*<<< orphan*/  ecore_emul_link_init_bb (struct ecore_hwfn*,struct ecore_ptt*) ; 

__attribute__((used)) static void ecore_emul_link_init(struct ecore_hwfn *p_hwfn,
				 struct ecore_ptt *p_ptt)
{
	if (ECORE_IS_AH(p_hwfn->p_dev) || ECORE_IS_E5(p_hwfn->p_dev))
		ecore_emul_link_init_ah_e5(p_hwfn, p_ptt);
	else /* BB */
		ecore_emul_link_init_bb(p_hwfn, p_ptt);

	return;
}