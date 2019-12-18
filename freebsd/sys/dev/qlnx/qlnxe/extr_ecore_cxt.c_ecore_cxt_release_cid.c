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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CXT_PF_CID ; 
 int /*<<< orphan*/  _ecore_cxt_release_cid (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ecore_cxt_release_cid(struct ecore_hwfn *p_hwfn, u32 cid)
{
	_ecore_cxt_release_cid(p_hwfn, cid, ECORE_CXT_PF_CID);
}