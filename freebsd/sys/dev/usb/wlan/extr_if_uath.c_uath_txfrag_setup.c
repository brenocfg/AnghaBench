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
typedef  int /*<<< orphan*/  uath_datahead ;
struct uath_softc {int dummy; } ;
struct uath_data {int dummy; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct uath_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UATH_ASSERT_LOCKED (struct uath_softc*) ; 
 int /*<<< orphan*/  ieee80211_node_incref (struct ieee80211_node*) ; 
 int /*<<< orphan*/  next ; 
 struct uath_data* uath_getbuf (struct uath_softc*) ; 
 int /*<<< orphan*/  uath_txfrag_cleanup (struct uath_softc*,int /*<<< orphan*/ *,struct ieee80211_node*) ; 

__attribute__((used)) static int
uath_txfrag_setup(struct uath_softc *sc, uath_datahead *frags,
    struct mbuf *m0, struct ieee80211_node *ni)
{
	struct mbuf *m;
	struct uath_data *bf;

	UATH_ASSERT_LOCKED(sc);
	for (m = m0->m_nextpkt; m != NULL; m = m->m_nextpkt) {
		bf = uath_getbuf(sc);
		if (bf == NULL) {       /* out of buffers, cleanup */
			uath_txfrag_cleanup(sc, frags, ni);
			break;
		}
		ieee80211_node_incref(ni);
		STAILQ_INSERT_TAIL(frags, bf, next);
	}

	return !STAILQ_EMPTY(frags);
}