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
struct ikev2_payloads {int /*<<< orphan*/  encr_next_payload; int /*<<< orphan*/  encrypted_len; scalar_t__ encrypted; int /*<<< orphan*/  nonce_len; int /*<<< orphan*/  nonce; int /*<<< orphan*/  ke_len; int /*<<< orphan*/  ke; int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa; } ;
struct ikev2_initiator_data {int /*<<< orphan*/  state; int /*<<< orphan*/  r_spi; } ;
struct ikev2_hdr {int /*<<< orphan*/  r_spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IKEV2_SPI_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  SA_AUTH ; 
 scalar_t__ ikev2_derive_keys (struct ikev2_initiator_data*) ; 
 scalar_t__ ikev2_process_ker (struct ikev2_initiator_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_process_nr (struct ikev2_initiator_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_process_sa_init_encr (struct ikev2_initiator_data*,struct ikev2_hdr const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ikev2_process_sar1 (struct ikev2_initiator_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ikev2_process_sa_init(struct ikev2_initiator_data *data,
				 const struct ikev2_hdr *hdr,
				 struct ikev2_payloads *pl)
{
	if (ikev2_process_sar1(data, pl->sa, pl->sa_len) < 0 ||
	    ikev2_process_ker(data, pl->ke, pl->ke_len) < 0 ||
	    ikev2_process_nr(data, pl->nonce, pl->nonce_len) < 0)
		return -1;

	os_memcpy(data->r_spi, hdr->r_spi, IKEV2_SPI_LEN);

	if (ikev2_derive_keys(data) < 0)
		return -1;

	if (pl->encrypted) {
		wpa_printf(MSG_DEBUG, "IKEV2: Encrypted payload in SA_INIT - "
			   "try to get IDr from it");
		if (ikev2_process_sa_init_encr(data, hdr, pl->encrypted,
					       pl->encrypted_len,
					       pl->encr_next_payload) < 0) {
			wpa_printf(MSG_INFO, "IKEV2: Failed to process "
				   "encrypted payload");
			return -1;
		}
	}

	data->state = SA_AUTH;

	return 0;
}