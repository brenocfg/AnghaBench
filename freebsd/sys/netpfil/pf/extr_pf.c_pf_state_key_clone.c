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
struct pf_state_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  V_pf_state_key_z ; 
 int /*<<< orphan*/  bcopy (struct pf_state_key*,struct pf_state_key*,int) ; 
 struct pf_state_key* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pf_state_key *
pf_state_key_clone(struct pf_state_key *orig)
{
	struct pf_state_key *sk;

	sk = uma_zalloc(V_pf_state_key_z, M_NOWAIT);
	if (sk == NULL)
		return (NULL);

	bcopy(orig, sk, sizeof(struct pf_state_key_cmp));

	return (sk);
}