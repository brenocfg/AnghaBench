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
struct TYPE_4__ {scalar_t__ type; } ;
struct e1000_dev_spec_82543 {int /*<<< orphan*/  tbi_compatibility; } ;
struct TYPE_3__ {struct e1000_dev_spec_82543 _82543; } ;
struct e1000_hw {TYPE_2__ mac; TYPE_1__ dev_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  DEBUGOUT (char*) ; 
 int /*<<< orphan*/  TBI_COMPAT_ENABLED ; 
 scalar_t__ e1000_82543 ; 

void e1000_set_tbi_compatibility_82543(struct e1000_hw *hw, bool state)
{
	struct e1000_dev_spec_82543 *dev_spec = &hw->dev_spec._82543;

	DEBUGFUNC("e1000_set_tbi_compatibility_82543");

	if (hw->mac.type != e1000_82543) {
		DEBUGOUT("TBI compatibility workaround for 82543 only.\n");
		goto out;
	}

	if (state)
		dev_spec->tbi_compatibility |= TBI_COMPAT_ENABLED;
	else
		dev_spec->tbi_compatibility &= ~TBI_COMPAT_ENABLED;

out:
	return;
}