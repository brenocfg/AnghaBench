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
typedef  void* u_int16_t ;
struct pf_state_key {int /*<<< orphan*/  af; int /*<<< orphan*/  proto; void** port; int /*<<< orphan*/ * addr; } ;
struct pf_pdesc {size_t sidx; size_t didx; int /*<<< orphan*/  af; int /*<<< orphan*/  proto; } ;
struct pf_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PF_ACPY (int /*<<< orphan*/ *,struct pf_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_state_key_z ; 
 struct pf_state_key* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pf_state_key *
pf_state_key_setup(struct pf_pdesc *pd, struct pf_addr *saddr,
	struct pf_addr *daddr, u_int16_t sport, u_int16_t dport)
{
	struct pf_state_key *sk;

	sk = uma_zalloc(V_pf_state_key_z, M_NOWAIT);
	if (sk == NULL)
		return (NULL);

	PF_ACPY(&sk->addr[pd->sidx], saddr, pd->af);
	PF_ACPY(&sk->addr[pd->didx], daddr, pd->af);
	sk->port[pd->sidx] = sport;
	sk->port[pd->didx] = dport;
	sk->proto = pd->proto;
	sk->af = pd->af;

	return (sk);
}