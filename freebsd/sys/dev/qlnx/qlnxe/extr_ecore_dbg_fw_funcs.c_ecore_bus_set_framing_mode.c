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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum dbg_bus_frame_modes { ____Placeholder_dbg_bus_frame_modes } dbg_bus_frame_modes ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_REG_FRAMING_MODE ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_bus_set_framing_mode(struct ecore_hwfn *p_hwfn,
									   struct ecore_ptt *p_ptt,
									   enum dbg_bus_frame_modes mode)
{
	ecore_wr(p_hwfn, p_ptt, DBG_REG_FRAMING_MODE, (u8)mode);
}