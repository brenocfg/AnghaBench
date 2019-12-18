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
struct tcp_hpts_entry {int dummy; } ;
struct inpcb {size_t inp_hpts_cpu; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {struct tcp_hpts_entry** rp_ent; } ;

/* Variables and functions */
 TYPE_1__ tcp_pace ; 

struct tcp_hpts_entry *
tcp_cur_hpts(struct inpcb *inp)
{
	int32_t hpts_num;
	struct tcp_hpts_entry *hpts;

	hpts_num = inp->inp_hpts_cpu;
	hpts = tcp_pace.rp_ent[hpts_num];
	return (hpts);
}