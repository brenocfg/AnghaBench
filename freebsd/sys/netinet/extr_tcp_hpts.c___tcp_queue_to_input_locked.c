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
struct tcp_hpts_entry {scalar_t__ p_hpts_active; int p_direct_wake; } ;
struct inpcb {scalar_t__ inp_in_input; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPTS_MTX_ASSERT (struct tcp_hpts_entry*) ; 
 int /*<<< orphan*/  hpts_sane_input_insert (struct tcp_hpts_entry*,struct inpcb*,int) ; 
 int /*<<< orphan*/  tcp_wakeinput (struct tcp_hpts_entry*) ; 

int
__tcp_queue_to_input_locked(struct inpcb *inp, struct tcp_hpts_entry *hpts, int32_t line)
{
	int32_t retval = 0;

	HPTS_MTX_ASSERT(hpts);
	if (inp->inp_in_input == 0) {
		/* Ok we need to set it on the hpts in the current slot */
		hpts_sane_input_insert(hpts, inp, line);
		retval = 1;
		if (hpts->p_hpts_active == 0) {
			/*
			 * Activate the hpts if it is sleeping.
			 */
			retval = 2;
			hpts->p_direct_wake = 1;
			tcp_wakeinput(hpts);
		}
	} else if (hpts->p_hpts_active == 0) {
		retval = 4;
		hpts->p_direct_wake = 1;
		tcp_wakeinput(hpts);
	}
	return (retval);
}