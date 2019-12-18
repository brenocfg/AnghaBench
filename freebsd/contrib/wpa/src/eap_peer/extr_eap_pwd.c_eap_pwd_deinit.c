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
struct eap_sm {int dummy; } ;
struct TYPE_3__ {TYPE_2__* range; } ;
struct eap_pwd_data {int id_peer_len; int id_server_len; int password_len; TYPE_1__ allowed_groups; int /*<<< orphan*/  outbuf; int /*<<< orphan*/  inbuf; TYPE_2__* grp; struct eap_pwd_data* password; struct eap_pwd_data* id_server; struct eap_pwd_data* id_peer; int /*<<< orphan*/  server_element; int /*<<< orphan*/  my_element; int /*<<< orphan*/  k; int /*<<< orphan*/  my_scalar; int /*<<< orphan*/  server_scalar; int /*<<< orphan*/  private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/  pwe; int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  bin_clear_free (struct eap_pwd_data*,int) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_ec_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (TYPE_2__*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_pwd_deinit(struct eap_sm *sm, void *priv)
{
	struct eap_pwd_data *data = priv;

	crypto_bignum_deinit(data->private_value, 1);
	crypto_bignum_deinit(data->server_scalar, 1);
	crypto_bignum_deinit(data->my_scalar, 1);
	crypto_bignum_deinit(data->k, 1);
	crypto_ec_point_deinit(data->my_element, 1);
	crypto_ec_point_deinit(data->server_element, 1);
	bin_clear_free(data->id_peer, data->id_peer_len);
	bin_clear_free(data->id_server, data->id_server_len);
	bin_clear_free(data->password, data->password_len);
	if (data->grp) {
		crypto_ec_deinit(data->grp->group);
		crypto_ec_point_deinit(data->grp->pwe, 1);
		os_free(data->grp);
	}
	wpabuf_free(data->inbuf);
	wpabuf_free(data->outbuf);
	os_free(data->allowed_groups.range);
	bin_clear_free(data, sizeof(*data));
}