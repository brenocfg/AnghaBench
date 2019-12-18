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
struct TYPE_2__ {int type; } ;
union if_snd_tag_alloc_params {TYPE_1__ hdr; } ;
struct m_snd_tag {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IF_SND_TAG_TYPE_RATE_LIMIT 129 
#define  IF_SND_TAG_TYPE_UNLIMITED 128 
 int mlx5e_rl_snd_tag_alloc (struct ifnet*,union if_snd_tag_alloc_params*,struct m_snd_tag**) ; 
 int mlx5e_ul_snd_tag_alloc (struct ifnet*,union if_snd_tag_alloc_params*,struct m_snd_tag**) ; 

__attribute__((used)) static int
mlx5e_snd_tag_alloc(struct ifnet *ifp,
    union if_snd_tag_alloc_params *params,
    struct m_snd_tag **ppmt)
{

	switch (params->hdr.type) {
#ifdef RATELIMIT
	case IF_SND_TAG_TYPE_RATE_LIMIT:
		return (mlx5e_rl_snd_tag_alloc(ifp, params, ppmt));
#endif
	case IF_SND_TAG_TYPE_UNLIMITED:
		return (mlx5e_ul_snd_tag_alloc(ifp, params, ppmt));
	default:
		return (EOPNOTSUPP);
	}
}