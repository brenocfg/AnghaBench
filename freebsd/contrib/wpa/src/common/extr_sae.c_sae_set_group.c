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
struct sae_temporary_data {scalar_t__ prime_len; scalar_t__ order_len; int /*<<< orphan*/ * order_buf; int /*<<< orphan*/ * order; TYPE_1__* dh; int /*<<< orphan*/ * prime_buf; int /*<<< orphan*/ * prime; scalar_t__ ec; } ;
struct sae_data {int group; struct sae_temporary_data* tmp; } ;
struct TYPE_2__ {scalar_t__ prime_len; scalar_t__ order_len; int /*<<< orphan*/  order; int /*<<< orphan*/  prime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SAE_MAX_PRIME_LEN ; 
 void* crypto_bignum_init_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * crypto_ec_get_order (scalar_t__) ; 
 int /*<<< orphan*/ * crypto_ec_get_prime (scalar_t__) ; 
 scalar_t__ crypto_ec_init (int) ; 
 scalar_t__ crypto_ec_order_len (scalar_t__) ; 
 scalar_t__ crypto_ec_prime_len (scalar_t__) ; 
 TYPE_1__* dh_groups_get (int) ; 
 int /*<<< orphan*/  dragonfly_suitable_group (int,int /*<<< orphan*/ ) ; 
 struct sae_temporary_data* os_zalloc (int) ; 
 int /*<<< orphan*/  sae_clear_data (struct sae_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

int sae_set_group(struct sae_data *sae, int group)
{
	struct sae_temporary_data *tmp;

#ifdef CONFIG_TESTING_OPTIONS
	/* Allow all groups for testing purposes in non-production builds. */
#else /* CONFIG_TESTING_OPTIONS */
	if (!dragonfly_suitable_group(group, 0)) {
		wpa_printf(MSG_DEBUG, "SAE: Reject unsuitable group %d", group);
		return -1;
	}
#endif /* CONFIG_TESTING_OPTIONS */

	sae_clear_data(sae);
	tmp = sae->tmp = os_zalloc(sizeof(*tmp));
	if (tmp == NULL)
		return -1;

	/* First, check if this is an ECC group */
	tmp->ec = crypto_ec_init(group);
	if (tmp->ec) {
		wpa_printf(MSG_DEBUG, "SAE: Selecting supported ECC group %d",
			   group);
		sae->group = group;
		tmp->prime_len = crypto_ec_prime_len(tmp->ec);
		tmp->prime = crypto_ec_get_prime(tmp->ec);
		tmp->order_len = crypto_ec_order_len(tmp->ec);
		tmp->order = crypto_ec_get_order(tmp->ec);
		return 0;
	}

	/* Not an ECC group, check FFC */
	tmp->dh = dh_groups_get(group);
	if (tmp->dh) {
		wpa_printf(MSG_DEBUG, "SAE: Selecting supported FFC group %d",
			   group);
		sae->group = group;
		tmp->prime_len = tmp->dh->prime_len;
		if (tmp->prime_len > SAE_MAX_PRIME_LEN) {
			sae_clear_data(sae);
			return -1;
		}

		tmp->prime_buf = crypto_bignum_init_set(tmp->dh->prime,
							tmp->prime_len);
		if (tmp->prime_buf == NULL) {
			sae_clear_data(sae);
			return -1;
		}
		tmp->prime = tmp->prime_buf;

		tmp->order_len = tmp->dh->order_len;
		tmp->order_buf = crypto_bignum_init_set(tmp->dh->order,
							tmp->dh->order_len);
		if (tmp->order_buf == NULL) {
			sae_clear_data(sae);
			return -1;
		}
		tmp->order = tmp->order_buf;

		return 0;
	}

	/* Unsupported group */
	wpa_printf(MSG_DEBUG,
		   "SAE: Group %d not supported by the crypto library", group);
	return -1;
}