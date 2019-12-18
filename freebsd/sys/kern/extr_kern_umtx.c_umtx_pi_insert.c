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
struct umtxq_chain {int /*<<< orphan*/  uc_pi_list; } ;
struct umtx_pi {int /*<<< orphan*/  pi_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct umtx_pi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (struct umtxq_chain*) ; 
 int /*<<< orphan*/  pi_hashlink ; 
 struct umtxq_chain* umtxq_getchain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
umtx_pi_insert(struct umtx_pi *pi)
{
	struct umtxq_chain *uc;

	uc = umtxq_getchain(&pi->pi_key);
	UMTXQ_LOCKED_ASSERT(uc);
	TAILQ_INSERT_TAIL(&uc->uc_pi_list, pi, pi_hashlink);
}