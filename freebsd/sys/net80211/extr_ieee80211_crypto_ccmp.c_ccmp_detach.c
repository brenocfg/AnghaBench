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
struct ieee80211_key {struct ccmp_ctx* wk_private; } ;
struct ccmp_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FREE (struct ccmp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_80211_CRYPTO ; 
 scalar_t__ nrefs ; 

__attribute__((used)) static void
ccmp_detach(struct ieee80211_key *k)
{
	struct ccmp_ctx *ctx = k->wk_private;

	IEEE80211_FREE(ctx, M_80211_CRYPTO);
	KASSERT(nrefs > 0, ("imbalanced attach/detach"));
	nrefs--;			/* NB: we assume caller locking */
}