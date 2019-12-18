#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drbg_state {int fips_primed; TYPE_2__* d_ops; void* prev; TYPE_1__* core; void* scratchpadbuf; void* scratchpad; void* Cbuf; void* C; void* Vbuf; void* V; } ;
struct TYPE_6__ {int (* crypto_init ) (struct drbg_state*) ;int /*<<< orphan*/  (* crypto_fini ) (struct drbg_state*) ;} ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_CRYPTO_FIPS ; 
#define  DRBG_CTR 130 
#define  DRBG_HASH 129 
#define  DRBG_HMAC 128 
 int DRBG_TYPE_MASK ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 void* PTR_ALIGN (void*,int) ; 
 int drbg_blocklen (struct drbg_state*) ; 
 TYPE_2__ drbg_ctr_ops ; 
 int /*<<< orphan*/  drbg_dealloc_state (struct drbg_state*) ; 
 TYPE_2__ drbg_hash_ops ; 
 TYPE_2__ drbg_hmac_ops ; 
 unsigned int drbg_sec_strength (int const) ; 
 int drbg_statelen (struct drbg_state*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int stub1 (struct drbg_state*) ; 
 int /*<<< orphan*/  stub2 (struct drbg_state*) ; 

__attribute__((used)) static inline int drbg_alloc_state(struct drbg_state *drbg)
{
	int ret = -ENOMEM;
	unsigned int sb_size = 0;

	switch (drbg->core->flags & DRBG_TYPE_MASK) {
#ifdef CONFIG_CRYPTO_DRBG_HMAC
	case DRBG_HMAC:
		drbg->d_ops = &drbg_hmac_ops;
		break;
#endif /* CONFIG_CRYPTO_DRBG_HMAC */
#ifdef CONFIG_CRYPTO_DRBG_HASH
	case DRBG_HASH:
		drbg->d_ops = &drbg_hash_ops;
		break;
#endif /* CONFIG_CRYPTO_DRBG_HASH */
#ifdef CONFIG_CRYPTO_DRBG_CTR
	case DRBG_CTR:
		drbg->d_ops = &drbg_ctr_ops;
		break;
#endif /* CONFIG_CRYPTO_DRBG_CTR */
	default:
		ret = -EOPNOTSUPP;
		goto err;
	}

	ret = drbg->d_ops->crypto_init(drbg);
	if (ret < 0)
		goto err;

	drbg->Vbuf = kmalloc(drbg_statelen(drbg) + ret, GFP_KERNEL);
	if (!drbg->Vbuf) {
		ret = -ENOMEM;
		goto fini;
	}
	drbg->V = PTR_ALIGN(drbg->Vbuf, ret + 1);
	drbg->Cbuf = kmalloc(drbg_statelen(drbg) + ret, GFP_KERNEL);
	if (!drbg->Cbuf) {
		ret = -ENOMEM;
		goto fini;
	}
	drbg->C = PTR_ALIGN(drbg->Cbuf, ret + 1);
	/* scratchpad is only generated for CTR and Hash */
	if (drbg->core->flags & DRBG_HMAC)
		sb_size = 0;
	else if (drbg->core->flags & DRBG_CTR)
		sb_size = drbg_statelen(drbg) + drbg_blocklen(drbg) + /* temp */
			  drbg_statelen(drbg) +	/* df_data */
			  drbg_blocklen(drbg) +	/* pad */
			  drbg_blocklen(drbg) +	/* iv */
			  drbg_statelen(drbg) + drbg_blocklen(drbg); /* temp */
	else
		sb_size = drbg_statelen(drbg) + drbg_blocklen(drbg);

	if (0 < sb_size) {
		drbg->scratchpadbuf = kzalloc(sb_size + ret, GFP_KERNEL);
		if (!drbg->scratchpadbuf) {
			ret = -ENOMEM;
			goto fini;
		}
		drbg->scratchpad = PTR_ALIGN(drbg->scratchpadbuf, ret + 1);
	}

	if (IS_ENABLED(CONFIG_CRYPTO_FIPS)) {
		drbg->prev = kzalloc(drbg_sec_strength(drbg->core->flags),
				     GFP_KERNEL);
		if (!drbg->prev)
			goto fini;
		drbg->fips_primed = false;
	}

	return 0;

fini:
	drbg->d_ops->crypto_fini(drbg);
err:
	drbg_dealloc_state(drbg);
	return ret;
}