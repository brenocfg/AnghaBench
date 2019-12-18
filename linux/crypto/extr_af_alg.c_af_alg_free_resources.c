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
struct af_alg_async_req {int /*<<< orphan*/  areqlen; struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  af_alg_free_areq_sgls (struct af_alg_async_req*) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct af_alg_async_req*,int /*<<< orphan*/ ) ; 

void af_alg_free_resources(struct af_alg_async_req *areq)
{
	struct sock *sk = areq->sk;

	af_alg_free_areq_sgls(areq);
	sock_kfree_s(sk, areq, areq->areqlen);
}