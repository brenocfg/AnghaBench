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
struct tcp_hpts_entry {int /*<<< orphan*/ * p_hptss; } ;
struct inpcb {size_t inp_hptsslot; scalar_t__ inp_in_hpts; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hpts_sane_pace_remove (struct tcp_hpts_entry*,struct inpcb*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_remove_hpts_ref (struct inpcb*,struct tcp_hpts_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_hpts_remove_locked_output(struct tcp_hpts_entry *hpts, struct inpcb *inp, int32_t flags, int32_t line)
{
	if (inp->inp_in_hpts) {
		hpts_sane_pace_remove(hpts, inp, &hpts->p_hptss[inp->inp_hptsslot], 1);
		tcp_remove_hpts_ref(inp, hpts, line);
	}
}