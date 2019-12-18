#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ flowtype; int flowid; } ;
union if_snd_tag_alloc_params {TYPE_2__ hdr; } ;
typedef  int u32 ;
struct TYPE_5__ {int num_channels; } ;
struct mlx5e_priv {struct mlx5e_channel* channel; TYPE_1__ params; scalar_t__ gone; } ;
struct m_snd_tag {int dummy; } ;
struct TYPE_8__ {struct m_snd_tag m_snd_tag; } ;
struct mlx5e_channel {TYPE_4__ tag; TYPE_3__* sq; } ;
struct ifnet {struct mlx5e_priv* if_softc; } ;
struct TYPE_7__ {scalar_t__ running; } ;

/* Variables and functions */
 int ENXIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 int /*<<< orphan*/  m_snd_tag_ref (struct m_snd_tag*) ; 
 scalar_t__ rss_hash2bucket (int,scalar_t__,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
mlx5e_ul_snd_tag_alloc(struct ifnet *ifp,
    union if_snd_tag_alloc_params *params,
    struct m_snd_tag **ppmt)
{
	struct mlx5e_priv *priv;
	struct mlx5e_channel *pch;

	priv = ifp->if_softc;

	if (unlikely(priv->gone || params->hdr.flowtype == M_HASHTYPE_NONE)) {
		return (EOPNOTSUPP);
	} else {
		/* keep this code synced with mlx5e_select_queue() */
		u32 ch = priv->params.num_channels;
#ifdef RSS
		u32 temp;

		if (rss_hash2bucket(params->hdr.flowid,
		    params->hdr.flowtype, &temp) == 0)
			ch = temp % ch;
		else
#endif
			ch = (params->hdr.flowid % 128) % ch;

		/*
		 * NOTE: The channels array is only freed at detach
		 * and it safe to return a pointer to the send tag
		 * inside the channels structure as long as we
		 * reference the priv.
		 */
		pch = priv->channel + ch;

		/* check if send queue is not running */
		if (unlikely(pch->sq[0].running == 0))
			return (ENXIO);
		m_snd_tag_ref(&pch->tag.m_snd_tag);
		*ppmt = &pch->tag.m_snd_tag;
		return (0);
	}
}