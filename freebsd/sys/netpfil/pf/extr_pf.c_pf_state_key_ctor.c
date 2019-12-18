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
struct pf_state_key_cmp {int dummy; } ;
struct pf_state_key {int /*<<< orphan*/ * states; } ;

/* Variables and functions */
 size_t PF_SK_STACK ; 
 size_t PF_SK_WIRE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct pf_state_key*,int) ; 

__attribute__((used)) static int
pf_state_key_ctor(void *mem, int size, void *arg, int flags)
{
	struct pf_state_key *sk = mem;

	bzero(sk, sizeof(struct pf_state_key_cmp));
	TAILQ_INIT(&sk->states[PF_SK_WIRE]);
	TAILQ_INIT(&sk->states[PF_SK_STACK]);

	return (0);
}