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
struct wpabuf {int dummy; } ;
struct sae_data {int send_confirm; TYPE_1__* tmp; int /*<<< orphan*/  peer_commit_scalar; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer_commit_element_ffc; int /*<<< orphan*/  own_commit_element_ffc; int /*<<< orphan*/  own_commit_scalar; int /*<<< orphan*/  peer_commit_element_ecc; int /*<<< orphan*/  own_commit_element_ecc; scalar_t__ ec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256_MAC_LEN ; 
 int /*<<< orphan*/  sae_cn_confirm_ecc (struct sae_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sae_cn_confirm_ffc (struct sae_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 

void sae_write_confirm(struct sae_data *sae, struct wpabuf *buf)
{
	const u8 *sc;

	if (sae->tmp == NULL)
		return;

	/* Send-Confirm */
	sc = wpabuf_put(buf, 0);
	wpabuf_put_le16(buf, sae->send_confirm);
	if (sae->send_confirm < 0xffff)
		sae->send_confirm++;

	if (sae->tmp->ec)
		sae_cn_confirm_ecc(sae, sc, sae->tmp->own_commit_scalar,
				   sae->tmp->own_commit_element_ecc,
				   sae->peer_commit_scalar,
				   sae->tmp->peer_commit_element_ecc,
				   wpabuf_put(buf, SHA256_MAC_LEN));
	else
		sae_cn_confirm_ffc(sae, sc, sae->tmp->own_commit_scalar,
				   sae->tmp->own_commit_element_ffc,
				   sae->peer_commit_scalar,
				   sae->tmp->peer_commit_element_ffc,
				   wpabuf_put(buf, SHA256_MAC_LEN));
}