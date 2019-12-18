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
struct umtxq_chain {int dummy; } ;
struct umtx_key {scalar_t__ type; size_t hash; } ;

/* Variables and functions */
 scalar_t__ TYPE_SEM ; 
 struct umtxq_chain** umtxq_chains ; 

__attribute__((used)) static inline struct umtxq_chain *
umtxq_getchain(struct umtx_key *key)
{

	if (key->type <= TYPE_SEM)
		return (&umtxq_chains[1][key->hash]);
	return (&umtxq_chains[0][key->hash]);
}