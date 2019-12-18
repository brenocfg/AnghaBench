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
typedef  int /*<<< orphan*/  u64 ;
struct se_crypto_request {int /*<<< orphan*/ * comp; } ;
struct nitrox_kcrypt_request {scalar_t__ dst; struct se_crypto_request creq; } ;

/* Variables and functions */
 scalar_t__ ORH_HLEN ; 
 int /*<<< orphan*/  set_comp_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nitrox_creq_set_comp(struct nitrox_kcrypt_request *nkreq)
{
	struct se_crypto_request *creq = &nkreq->creq;

	creq->comp = (u64 *)(nkreq->dst + ORH_HLEN);
	set_comp_value(creq->comp);
}