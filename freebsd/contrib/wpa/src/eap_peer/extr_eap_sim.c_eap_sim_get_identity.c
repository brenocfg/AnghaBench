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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct eap_sim_data {size_t reauth_id_len; size_t pseudonym_len; int /*<<< orphan*/  const* pseudonym; int /*<<< orphan*/  const* reauth_id; } ;

/* Variables and functions */

__attribute__((used)) static const u8 * eap_sim_get_identity(struct eap_sm *sm, void *priv,
				       size_t *len)
{
	struct eap_sim_data *data = priv;

	if (data->reauth_id) {
		*len = data->reauth_id_len;
		return data->reauth_id;
	}

	if (data->pseudonym) {
		*len = data->pseudonym_len;
		return data->pseudonym;
	}

	return NULL;
}