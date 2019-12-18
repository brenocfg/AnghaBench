#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int m_skt; } ;
struct TYPE_9__ {int m_skt; } ;
struct TYPE_7__ {int m_skt; } ;
struct TYPE_6__ {int /*<<< orphan*/  n_skt; } ;
union uvh_rh_gam_config_mmr_u {TYPE_5__ s1; TYPE_4__ s2; TYPE_2__ s3; TYPE_1__ s; void* v; } ;
struct TYPE_8__ {int m_skt; } ;
union uv3h_gr0_gam_gr_config_u {TYPE_3__ s3; void* v; } ;
struct mn {int m_val; int n_lshift; int /*<<< orphan*/  m_shift; int /*<<< orphan*/  n_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  UV3H_GR0_GAM_GR_CONFIG ; 
 int /*<<< orphan*/  UVH_RH_GAM_CONFIG_MMR ; 
 scalar_t__ is_uv1_hub () ; 
 scalar_t__ is_uv2_hub () ; 
 scalar_t__ is_uv3_hub () ; 
 scalar_t__ is_uv4_hub () ; 
 int /*<<< orphan*/  memset (struct mn*,int /*<<< orphan*/ ,int) ; 
 void* uv_read_local_mmr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_mn(struct mn *mnp)
{
	union uvh_rh_gam_config_mmr_u m_n_config;
	union uv3h_gr0_gam_gr_config_u m_gr_config;

	/* Make sure the whole structure is well initialized: */
	memset(mnp, 0, sizeof(*mnp));

	m_n_config.v	= uv_read_local_mmr(UVH_RH_GAM_CONFIG_MMR);
	mnp->n_val	= m_n_config.s.n_skt;

	if (is_uv4_hub()) {
		mnp->m_val	= 0;
		mnp->n_lshift	= 0;
	} else if (is_uv3_hub()) {
		mnp->m_val	= m_n_config.s3.m_skt;
		m_gr_config.v	= uv_read_local_mmr(UV3H_GR0_GAM_GR_CONFIG);
		mnp->n_lshift	= m_gr_config.s3.m_skt;
	} else if (is_uv2_hub()) {
		mnp->m_val	= m_n_config.s2.m_skt;
		mnp->n_lshift	= mnp->m_val == 40 ? 40 : 39;
	} else if (is_uv1_hub()) {
		mnp->m_val	= m_n_config.s1.m_skt;
		mnp->n_lshift	= mnp->m_val;
	}
	mnp->m_shift = mnp->m_val ? 64 - mnp->m_val : 0;
}