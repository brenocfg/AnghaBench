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
typedef  int /*<<< orphan*/  uint16_t ;
struct inpcb {size_t inp_hpts_cpu; } ;
struct TYPE_4__ {TYPE_1__** rp_ent; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_delayed_by; } ;

/* Variables and functions */
 TYPE_2__ tcp_pace ; 

uint16_t
tcp_hpts_delayedby(struct inpcb *inp){
	return (tcp_pace.rp_ent[inp->inp_hpts_cpu]->p_delayed_by);
}