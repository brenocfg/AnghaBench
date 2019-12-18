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
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 scalar_t__ e1000_pch2lan ; 
 int /*<<< orphan*/  e1000_resume_workarounds_pchlan (TYPE_2__*) ; 
 int /*<<< orphan*/  em_if_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_init_manageability (struct adapter*) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_if_resume(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);

	if (adapter->hw.mac.type == e1000_pch2lan)
		e1000_resume_workarounds_pchlan(&adapter->hw);
	em_if_init(ctx);
	em_init_manageability(adapter);

	return(0);
}