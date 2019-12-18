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
typedef  int /*<<< orphan*/  u8 ;
struct dpp_pkex {int /*<<< orphan*/ * peer_bootstrap_key; TYPE_1__* own_bi; } ;
struct dpp_global {int /*<<< orphan*/  bootstrap; } ;
struct dpp_bootstrap_info {int num_freq; unsigned int* freq; int /*<<< orphan*/  list; int /*<<< orphan*/ * pubkey; int /*<<< orphan*/  curve; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  curve; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPP_BOOTSTRAP_PKEX ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpp_bootstrap_info_free (struct dpp_bootstrap_info*) ; 
 scalar_t__ dpp_bootstrap_key_hash (struct dpp_bootstrap_info*) ; 
 int /*<<< orphan*/  dpp_next_id (struct dpp_global*) ; 
 int /*<<< orphan*/  dpp_pkex_free (struct dpp_pkex*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct dpp_bootstrap_info* os_zalloc (int) ; 

struct dpp_bootstrap_info *
dpp_pkex_finish(struct dpp_global *dpp, struct dpp_pkex *pkex, const u8 *peer,
		unsigned int freq)
{
	struct dpp_bootstrap_info *bi;

	bi = os_zalloc(sizeof(*bi));
	if (!bi)
		return NULL;
	bi->id = dpp_next_id(dpp);
	bi->type = DPP_BOOTSTRAP_PKEX;
	os_memcpy(bi->mac_addr, peer, ETH_ALEN);
	bi->num_freq = 1;
	bi->freq[0] = freq;
	bi->curve = pkex->own_bi->curve;
	bi->pubkey = pkex->peer_bootstrap_key;
	pkex->peer_bootstrap_key = NULL;
	if (dpp_bootstrap_key_hash(bi) < 0) {
		dpp_bootstrap_info_free(bi);
		return NULL;
	}
	dpp_pkex_free(pkex);
	dl_list_add(&dpp->bootstrap, &bi->list);
	return bi;
}