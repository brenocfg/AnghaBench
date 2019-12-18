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
typedef  unsigned long long uint64_t ;
typedef  unsigned long long u_int ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W_TCB_T_FLAGS ; 
 int set_tcb_field (struct adapter*,int,int /*<<< orphan*/ ,unsigned long long,unsigned long long,unsigned long long) ; 

__attribute__((used)) static inline int
set_tcb_tflag(struct adapter *sc, int tid, u_int bit_pos, u_int val,
    u_int no_reply)
{

	return (set_tcb_field(sc, tid,  W_TCB_T_FLAGS, 1ULL << bit_pos,
	    (uint64_t)val << bit_pos, no_reply));
}