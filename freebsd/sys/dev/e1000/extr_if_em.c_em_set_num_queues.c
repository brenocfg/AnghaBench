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
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
#define  e1000_82574 135 
#define  e1000_82575 134 
#define  e1000_82576 133 
#define  e1000_82580 132 
#define  e1000_i210 131 
#define  e1000_i211 130 
#define  e1000_i350 129 
#define  e1000_i354 128 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_set_num_queues(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	int maxqueues;

	/* Sanity check based on HW */
	switch (adapter->hw.mac.type) {
	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
		maxqueues = 8;
		break;
	case e1000_i210:
	case e1000_82575:
		maxqueues = 4;
		break;
	case e1000_i211:
	case e1000_82574:
		maxqueues = 2;
		break;
	default:
		maxqueues = 1;
		break;
	}

	return (maxqueues);
}