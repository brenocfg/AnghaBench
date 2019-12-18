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
struct d40_chan {TYPE_1__* lcpa; } ;
struct TYPE_2__ {int /*<<< orphan*/  lcsp3; } ;

/* Variables and functions */
 int D40_CHAN_REG_SDLNK ; 
 int D40_MEM_LCSP3_DLOS_MASK ; 
 int D40_SREG_LNK_PHYS_LNK_MASK ; 
 int /*<<< orphan*/ * chan_base (struct d40_chan*) ; 
 scalar_t__ chan_is_logical (struct d40_chan*) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool d40_tx_is_linked(struct d40_chan *d40c)
{
	bool is_link;

	if (chan_is_logical(d40c))
		is_link = readl(&d40c->lcpa->lcsp3) &  D40_MEM_LCSP3_DLOS_MASK;
	else
		is_link = readl(chan_base(d40c) + D40_CHAN_REG_SDLNK)
			  & D40_SREG_LNK_PHYS_LNK_MASK;

	return is_link;
}