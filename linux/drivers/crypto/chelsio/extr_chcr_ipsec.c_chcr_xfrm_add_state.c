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
struct TYPE_8__ {unsigned long offload_handle; } ;
struct TYPE_7__ {scalar_t__ aalgo; scalar_t__ calgo; scalar_t__ family; scalar_t__ mode; int flags; } ;
struct TYPE_5__ {scalar_t__ proto; } ;
struct xfrm_state {TYPE_4__ xso; TYPE_3__ props; int /*<<< orphan*/  geniv; scalar_t__ tfcpad; TYPE_2__* aead; scalar_t__ encap; TYPE_1__ id; } ;
struct ipsec_sa_entry {int esn; int /*<<< orphan*/  hmac_ctrl; } ;
struct TYPE_6__ {int alg_icv_len; int alg_key_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IPPROTO_ESP ; 
 scalar_t__ SADB_AALG_NONE ; 
 scalar_t__ SADB_X_CALG_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ XFRM_MODE_TRANSPORT ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 
 int XFRM_STATE_ESN ; 
 int /*<<< orphan*/  chcr_ipsec_setauthsize (struct xfrm_state*,struct ipsec_sa_entry*) ; 
 int /*<<< orphan*/  chcr_ipsec_setkey (struct xfrm_state*,struct ipsec_sa_entry*) ; 
 struct ipsec_sa_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_xfrm_add_state(struct xfrm_state *x)
{
	struct ipsec_sa_entry *sa_entry;
	int res = 0;

	if (x->props.aalgo != SADB_AALG_NONE) {
		pr_debug("CHCR: Cannot offload authenticated xfrm states\n");
		return -EINVAL;
	}
	if (x->props.calgo != SADB_X_CALG_NONE) {
		pr_debug("CHCR: Cannot offload compressed xfrm states\n");
		return -EINVAL;
	}
	if (x->props.family != AF_INET &&
	    x->props.family != AF_INET6) {
		pr_debug("CHCR: Only IPv4/6 xfrm state offloaded\n");
		return -EINVAL;
	}
	if (x->props.mode != XFRM_MODE_TRANSPORT &&
	    x->props.mode != XFRM_MODE_TUNNEL) {
		pr_debug("CHCR: Only transport and tunnel xfrm offload\n");
		return -EINVAL;
	}
	if (x->id.proto != IPPROTO_ESP) {
		pr_debug("CHCR: Only ESP xfrm state offloaded\n");
		return -EINVAL;
	}
	if (x->encap) {
		pr_debug("CHCR: Encapsulated xfrm state not offloaded\n");
		return -EINVAL;
	}
	if (!x->aead) {
		pr_debug("CHCR: Cannot offload xfrm states without aead\n");
		return -EINVAL;
	}
	if (x->aead->alg_icv_len != 128 &&
	    x->aead->alg_icv_len != 96) {
		pr_debug("CHCR: Cannot offload xfrm states with AEAD ICV length other than 96b & 128b\n");
	return -EINVAL;
	}
	if ((x->aead->alg_key_len != 128 + 32) &&
	    (x->aead->alg_key_len != 256 + 32)) {
		pr_debug("CHCR: Cannot offload xfrm states with AEAD key length other than 128/256 bit\n");
		return -EINVAL;
	}
	if (x->tfcpad) {
		pr_debug("CHCR: Cannot offload xfrm states with tfc padding\n");
		return -EINVAL;
	}
	if (!x->geniv) {
		pr_debug("CHCR: Cannot offload xfrm states without geniv\n");
		return -EINVAL;
	}
	if (strcmp(x->geniv, "seqiv")) {
		pr_debug("CHCR: Cannot offload xfrm states with geniv other than seqiv\n");
		return -EINVAL;
	}

	sa_entry = kzalloc(sizeof(*sa_entry), GFP_KERNEL);
	if (!sa_entry) {
		res = -ENOMEM;
		goto out;
	}

	sa_entry->hmac_ctrl = chcr_ipsec_setauthsize(x, sa_entry);
	if (x->props.flags & XFRM_STATE_ESN)
		sa_entry->esn = 1;
	chcr_ipsec_setkey(x, sa_entry);
	x->xso.offload_handle = (unsigned long)sa_entry;
	try_module_get(THIS_MODULE);
out:
	return res;
}