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
struct sockopt {int dummy; } ;
struct ip_fw_chain {int /*<<< orphan*/  nat; } ;
struct cfg_nat {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPFW_UH_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_UH_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  IPFW_WUNLOCK (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct cfg_nat*,int /*<<< orphan*/ ) ; 
 struct ip_fw_chain V_layer3_chain ; 
 int /*<<< orphan*/  _next ; 
 int /*<<< orphan*/  flush_nat_ptrs (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  free_nat_instance (struct cfg_nat*) ; 
 struct cfg_nat* lookup_nat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sooptcopyin (struct sockopt*,int*,int,int) ; 

__attribute__((used)) static int
ipfw_nat_del(struct sockopt *sopt)
{
	struct cfg_nat *ptr;
	struct ip_fw_chain *chain = &V_layer3_chain;
	int i;

	sooptcopyin(sopt, &i, sizeof i, sizeof i);
	/* XXX validate i */
	IPFW_UH_WLOCK(chain);
	ptr = lookup_nat(&chain->nat, i);
	if (ptr == NULL) {
		IPFW_UH_WUNLOCK(chain);
		return (EINVAL);
	}
	IPFW_WLOCK(chain);
	LIST_REMOVE(ptr, _next);
	flush_nat_ptrs(chain, i);
	IPFW_WUNLOCK(chain);
	IPFW_UH_WUNLOCK(chain);
	free_nat_instance(ptr);
	return (0);
}