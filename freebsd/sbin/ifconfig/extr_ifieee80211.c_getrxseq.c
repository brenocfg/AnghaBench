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
struct ieee80211req_sta_info {int isi_state; int* isi_rxseqs; } ;

/* Variables and functions */
 int IEEE80211_NODE_QOS ; 
 int IEEE80211_TID_SIZE ; 

__attribute__((used)) static int
getrxseq(const struct ieee80211req_sta_info *si)
{
	int i, rxseq;

	if ((si->isi_state & IEEE80211_NODE_QOS) == 0)
		return si->isi_rxseqs[0];
	/* XXX not right but usually what folks want */
	rxseq = 0;
	for (i = 0; i < IEEE80211_TID_SIZE; i++)
		if (si->isi_rxseqs[i] > rxseq)
			rxseq = si->isi_rxseqs[i];
	return rxseq;
}