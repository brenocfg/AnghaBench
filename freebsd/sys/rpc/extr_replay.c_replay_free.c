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
struct replay_cache_entry {size_t rce_hash; scalar_t__ rce_repbody; } ;
struct replay_cache {int /*<<< orphan*/  rc_size; int /*<<< orphan*/  rc_all; int /*<<< orphan*/ * rc_cache; int /*<<< orphan*/  rc_count; int /*<<< orphan*/  rc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_RPC ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct replay_cache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct replay_cache_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (scalar_t__) ; 
 scalar_t__ m_length (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rce_alllink ; 
 int /*<<< orphan*/  rce_link ; 

__attribute__((used)) static void
replay_free(struct replay_cache *rc, struct replay_cache_entry *rce)
{

	mtx_assert(&rc->rc_lock, MA_OWNED);

	rc->rc_count--;
	TAILQ_REMOVE(&rc->rc_cache[rce->rce_hash], rce, rce_link);
	TAILQ_REMOVE(&rc->rc_all, rce, rce_alllink);
	if (rce->rce_repbody) {
		rc->rc_size -= m_length(rce->rce_repbody, NULL);
		m_freem(rce->rce_repbody);
	}
	free(rce, M_RPC);
}