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
struct sock {int dummy; } ;

/* Variables and functions */
 unsigned long long TF_RX_QUIESCE_S ; 
 int /*<<< orphan*/  TF_RX_QUIESCE_V (int) ; 
 int chtls_set_tcb_field (struct sock*,int,unsigned long long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chtls_set_tcb_quiesce(struct sock *sk, int val)
{
	return chtls_set_tcb_field(sk, 1, (1ULL << TF_RX_QUIESCE_S),
				   TF_RX_QUIESCE_V(val));
}