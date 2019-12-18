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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  val; } ;
struct ecore_ilt_client_cfg {TYPE_1__ p_size; } ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {struct ecore_ilt_client_cfg* clients; } ;
typedef  enum ilt_clients { ____Placeholder_ilt_clients } ilt_clients ;

/* Variables and functions */
 int /*<<< orphan*/  ILT_PAGE_IN_BYTES (int /*<<< orphan*/ ) ; 

u32 ecore_cxt_get_ilt_page_size(struct ecore_hwfn *p_hwfn,
				enum ilt_clients ilt_client)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct ecore_ilt_client_cfg *p_cli = &p_mngr->clients[ilt_client];

	return ILT_PAGE_IN_BYTES(p_cli->p_size.val);
}