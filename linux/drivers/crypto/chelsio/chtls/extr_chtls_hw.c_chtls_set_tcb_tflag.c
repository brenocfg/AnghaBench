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
typedef  unsigned int u64 ;
struct sock {int dummy; } ;

/* Variables and functions */
 int chtls_set_tcb_field (struct sock*,int,unsigned long long,unsigned int) ; 

int chtls_set_tcb_tflag(struct sock *sk, unsigned int bit_pos, int val)
{
	return chtls_set_tcb_field(sk, 1, 1ULL << bit_pos,
				   (u64)val << bit_pos);
}