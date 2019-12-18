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
typedef  int /*<<< orphan*/  u8 ;
typedef  long u16 ;
struct TYPE_3__ {long dh; } ;
struct ikev2_initiator_data {int /*<<< orphan*/ * r_dh_public; TYPE_2__* dh; TYPE_1__ proposal; } ;
struct TYPE_4__ {size_t prime_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 long WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc_copy (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ikev2_process_ker(struct ikev2_initiator_data *data,
			     const u8 *ker, size_t ker_len)
{
	u16 group;

	/*
	 * Key Exchange Payload:
	 * DH Group # (16 bits)
	 * RESERVED (16 bits)
	 * Key Exchange Data (Diffie-Hellman public value)
	 */

	if (ker == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: KEr not received");
		return -1;
	}

	if (ker_len < 4 + 96) {
		wpa_printf(MSG_INFO, "IKEV2: Too show Key Exchange Payload");
		return -1;
	}

	group = WPA_GET_BE16(ker);
	wpa_printf(MSG_DEBUG, "IKEV2: KEr DH Group #%u", group);

	if (group != data->proposal.dh) {
		wpa_printf(MSG_DEBUG, "IKEV2: KEr DH Group #%u does not match "
			   "with the selected proposal (%u)",
			   group, data->proposal.dh);
		return -1;
	}

	if (data->dh == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Unsupported DH group");
		return -1;
	}

	/* RFC 4306, Section 3.4:
	 * The length of DH public value MUST be equal to the length of the
	 * prime modulus.
	 */
	if (ker_len - 4 != data->dh->prime_len) {
		wpa_printf(MSG_INFO, "IKEV2: Invalid DH public value length "
			   "%ld (expected %ld)",
			   (long) (ker_len - 4), (long) data->dh->prime_len);
		return -1;
	}

	wpabuf_free(data->r_dh_public);
	data->r_dh_public = wpabuf_alloc_copy(ker + 4, ker_len - 4);
	if (data->r_dh_public == NULL)
		return -1;

	wpa_hexdump_buf(MSG_DEBUG, "IKEV2: KEr Diffie-Hellman Public Value",
			data->r_dh_public);
	
	return 0;
}