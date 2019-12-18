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
struct inpcb {int inp_flags2; } ;

/* Variables and functions */
 int INP_PCBGROUPWILD ; 
 int /*<<< orphan*/  in_pcbwild_add (struct inpcb*) ; 
 int in_pcbwild_needed (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcbwild_remove (struct inpcb*) ; 

__attribute__((used)) static void
in_pcbwild_update_internal(struct inpcb *inp)
{
	int wildcard_needed;

	wildcard_needed = in_pcbwild_needed(inp);
	if (wildcard_needed && !(inp->inp_flags2 & INP_PCBGROUPWILD))
		in_pcbwild_add(inp);
	else if (!wildcard_needed && (inp->inp_flags2 & INP_PCBGROUPWILD))
		in_pcbwild_remove(inp);
}