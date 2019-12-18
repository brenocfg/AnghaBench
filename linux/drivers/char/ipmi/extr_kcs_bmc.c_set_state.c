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
struct kcs_bmc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCS_STATUS_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCS_STATUS_STATE_MASK ; 
 int /*<<< orphan*/  update_status_bits (struct kcs_bmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_state(struct kcs_bmc *kcs_bmc, u8 state)
{
	update_status_bits(kcs_bmc, KCS_STATUS_STATE_MASK,
					KCS_STATUS_STATE(state));
}