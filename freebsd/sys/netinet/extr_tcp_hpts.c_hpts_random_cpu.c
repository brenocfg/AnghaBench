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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct inpcb {int inp_input_cpu; int inp_hpts_cpu; scalar_t__ inp_hpts_cpu_set; scalar_t__ inp_input_cpu_set; } ;

/* Variables and functions */
 int arc4random () ; 
 int mp_ncpus ; 

__attribute__((used)) static uint16_t
hpts_random_cpu(struct inpcb *inp){
	/*
	 * No flow type set distribute the load randomly.
	 */
	uint16_t cpuid;
	uint32_t ran;

	/*
	 * If one has been set use it i.e. we want both in and out on the
	 * same hpts.
	 */
	if (inp->inp_input_cpu_set) {
		return (inp->inp_input_cpu);
	} else if (inp->inp_hpts_cpu_set) {
		return (inp->inp_hpts_cpu);
	}
	/* Nothing set use a random number */
	ran = arc4random();
	cpuid = (ran & 0xffff) % mp_ncpus;
	return (cpuid);
}