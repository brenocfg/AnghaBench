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
struct switch_dev {int dummy; } ;
struct mvsw61xx_state {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  is_indirect; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 
 int /*<<< orphan*/  r16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline u16
sr16(struct switch_dev *dev, int addr, int reg)
{
	struct mvsw61xx_state *state = get_state(dev);

	return r16(state->bus, state->is_indirect, state->base_addr, addr, reg);
}