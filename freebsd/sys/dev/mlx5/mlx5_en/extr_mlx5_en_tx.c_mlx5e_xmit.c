#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_sq {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int csum_flags; TYPE_1__* snd_tag; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct ifnet {int dummy; } ;
struct TYPE_3__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mlx5e_sq* mlx5e_select_queue (struct ifnet*,struct mbuf*) ; 
 struct mlx5e_sq* mlx5e_select_queue_by_send_tag (struct ifnet*,struct mbuf*) ; 
 int mlx5e_xmit_locked (struct ifnet*,struct mlx5e_sq*,struct mbuf*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int
mlx5e_xmit(struct ifnet *ifp, struct mbuf *mb)
{
	struct mlx5e_sq *sq;
	int ret;

	if (mb->m_pkthdr.csum_flags & CSUM_SND_TAG) {
		MPASS(mb->m_pkthdr.snd_tag->ifp == ifp);
		sq = mlx5e_select_queue_by_send_tag(ifp, mb);
		if (unlikely(sq == NULL)) {
			goto select_queue;
		}
	} else {
select_queue:
		sq = mlx5e_select_queue(ifp, mb);
		if (unlikely(sq == NULL)) {
			/* Free mbuf */
			m_freem(mb);

			/* Invalid send queue */
			return (ENXIO);
		}
	}

	mtx_lock(&sq->lock);
	ret = mlx5e_xmit_locked(ifp, sq, mb);
	mtx_unlock(&sq->lock);

	return (ret);
}