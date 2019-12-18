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
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_CXT_PF_CID ; 
 int _ecore_cxt_acquire_cid (struct ecore_hwfn*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum _ecore_status_t ecore_cxt_acquire_cid(struct ecore_hwfn *p_hwfn,
					   enum protocol_type type,
					   u32 *p_cid)
{
	return _ecore_cxt_acquire_cid(p_hwfn, type, p_cid, ECORE_CXT_PF_CID);
}