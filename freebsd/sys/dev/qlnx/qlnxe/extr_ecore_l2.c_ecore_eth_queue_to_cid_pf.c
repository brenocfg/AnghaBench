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
typedef  int /*<<< orphan*/  u16 ;
struct ecore_queue_start_common_params {int dummy; } ;
struct ecore_queue_cid {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_NULL ; 
 struct ecore_queue_cid* ecore_eth_queue_to_cid (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_queue_start_common_params*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ecore_queue_cid *
ecore_eth_queue_to_cid_pf(struct ecore_hwfn *p_hwfn, u16 opaque_fid,
			  bool b_is_rx,
			  struct ecore_queue_start_common_params *p_params)
{
	return ecore_eth_queue_to_cid(p_hwfn, opaque_fid, p_params, b_is_rx,
				      OSAL_NULL);
}