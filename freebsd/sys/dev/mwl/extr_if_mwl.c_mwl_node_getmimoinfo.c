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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int rsvd1; scalar_t__ rssi_a; scalar_t__ rssi_b; scalar_t__ rssi_c; int /*<<< orphan*/  nf_c; int /*<<< orphan*/  nf_b; int /*<<< orphan*/  nf_a; } ;
struct mwl_node {TYPE_2__ mn_ai; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_mimo_info {TYPE_1__* ch; } ;
typedef  int int8_t ;
struct TYPE_3__ {int /*<<< orphan*/ * noise; int /*<<< orphan*/ * rssi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVT (int /*<<< orphan*/ ,scalar_t__) ; 
 struct mwl_node* MWL_NODE_CONST (struct ieee80211_node const*) ; 

__attribute__((used)) static void
mwl_node_getmimoinfo(const struct ieee80211_node *ni,
	struct ieee80211_mimo_info *mi)
{
#define	CVT(_dst, _src) do {						\
	(_dst) = rssi + ((logdbtbl[_src] - logdbtbl[rssi_max]) >> 2);	\
	(_dst) = (_dst) > 64 ? 127 : ((_dst) << 1);			\
} while (0)
	static const int8_t logdbtbl[32] = {
	       0,   0,  24,  38,  48,  56,  62,  68, 
	      72,  76,  80,  83,  86,  89,  92,  94, 
	      96,  98, 100, 102, 104, 106, 107, 109, 
	     110, 112, 113, 115, 116, 117, 118, 119
	};
	const struct mwl_node *mn = MWL_NODE_CONST(ni);
	uint8_t rssi = mn->mn_ai.rsvd1/2;		/* XXX */
	uint32_t rssi_max;

	rssi_max = mn->mn_ai.rssi_a;
	if (mn->mn_ai.rssi_b > rssi_max)
		rssi_max = mn->mn_ai.rssi_b;
	if (mn->mn_ai.rssi_c > rssi_max)
		rssi_max = mn->mn_ai.rssi_c;

	CVT(mi->ch[0].rssi[0], mn->mn_ai.rssi_a);
	CVT(mi->ch[1].rssi[0], mn->mn_ai.rssi_b);
	CVT(mi->ch[2].rssi[0], mn->mn_ai.rssi_c);

	mi->ch[0].noise[0] = mn->mn_ai.nf_a;
	mi->ch[1].noise[0] = mn->mn_ai.nf_b;
	mi->ch[2].noise[0] = mn->mn_ai.nf_c;
#undef CVT
}