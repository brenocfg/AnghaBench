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
struct pf_state_key {int /*<<< orphan*/ * states; } ;
struct pf_state {struct pf_state_key** key; } ;
struct pf_keyhash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct pf_state_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_HASHROW_ASSERT (struct pf_keyhash*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pf_state*,int /*<<< orphan*/ ) ; 
 struct pf_keyhash* V_pf_keyhash ; 
 int /*<<< orphan*/  V_pf_state_key_z ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/ * key_list ; 
 size_t pf_hashkey (struct pf_state_key*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pf_state_key*) ; 

__attribute__((used)) static void
pf_state_key_detach(struct pf_state *s, int idx)
{
	struct pf_state_key *sk = s->key[idx];
#ifdef INVARIANTS
	struct pf_keyhash *kh = &V_pf_keyhash[pf_hashkey(sk)];

	PF_HASHROW_ASSERT(kh);
#endif
	TAILQ_REMOVE(&sk->states[idx], s, key_list[idx]);
	s->key[idx] = NULL;

	if (TAILQ_EMPTY(&sk->states[0]) && TAILQ_EMPTY(&sk->states[1])) {
		LIST_REMOVE(sk, entry);
		uma_zfree(V_pf_state_key_z, sk);
	}
}