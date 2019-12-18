#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dmar_domain {int pglvl; TYPE_1__* dmar; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw_cap; } ;

/* Variables and functions */
 int DMAR_CAP_SPS (int /*<<< orphan*/ ) ; 
#define  DMAR_CAP_SPS_1G 131 
#define  DMAR_CAP_SPS_1T 130 
#define  DMAR_CAP_SPS_2M 129 
#define  DMAR_CAP_SPS_512G 128 
 int nitems (int const*) ; 

int
domain_is_sp_lvl(struct dmar_domain *domain, int lvl)
{
	int alvl, cap_sps;
	static const int sagaw_sp[] = {
		DMAR_CAP_SPS_2M,
		DMAR_CAP_SPS_1G,
		DMAR_CAP_SPS_512G,
		DMAR_CAP_SPS_1T
	};

	alvl = domain->pglvl - lvl - 1;
	cap_sps = DMAR_CAP_SPS(domain->dmar->hw_cap);
	return (alvl < nitems(sagaw_sp) && (sagaw_sp[alvl] & cap_sps) != 0);
}