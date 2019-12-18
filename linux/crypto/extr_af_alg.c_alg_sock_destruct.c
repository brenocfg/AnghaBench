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
struct alg_sock {int /*<<< orphan*/  private; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  alg_do_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct alg_sock* alg_sk (struct sock*) ; 

__attribute__((used)) static void alg_sock_destruct(struct sock *sk)
{
	struct alg_sock *ask = alg_sk(sk);

	alg_do_release(ask->type, ask->private);
}