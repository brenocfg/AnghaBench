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
struct TYPE_2__ {int /*<<< orphan*/  integ; int /*<<< orphan*/  encr; } ;
struct ikev2_responder_data {int /*<<< orphan*/  keys; TYPE_1__ proposal; } ;
struct ikev2_payloads {int /*<<< orphan*/  encr_next_payload; int /*<<< orphan*/  encrypted_len; int /*<<< orphan*/  encrypted; } ;
struct ikev2_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ikev2_decrypt_payload (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct ikev2_hdr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int ikev2_process_sa_auth_decrypted (struct ikev2_responder_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ikev2_process_sa_auth(struct ikev2_responder_data *data,
				 const struct ikev2_hdr *hdr,
				 struct ikev2_payloads *pl)
{
	u8 *decrypted;
	size_t decrypted_len;
	int ret;

	decrypted = ikev2_decrypt_payload(data->proposal.encr,
					  data->proposal.integ,
					  &data->keys, 1, hdr, pl->encrypted,
					  pl->encrypted_len, &decrypted_len);
	if (decrypted == NULL)
		return -1;

	ret = ikev2_process_sa_auth_decrypted(data, pl->encr_next_payload,
					      decrypted, decrypted_len);
	os_free(decrypted);

	return ret;
}