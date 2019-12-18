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
struct eap_sim_msg {int dummy; } ;
struct eap_aka_data {scalar_t__ eap_method; int /*<<< orphan*/ * id_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_AKA_CHECKCODE_LEN ; 
 int /*<<< orphan*/  EAP_AKA_PRIME_CHECKCODE_LEN ; 
 int /*<<< orphan*/  EAP_SIM_AT_CHECKCODE ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  eap_sim_msg_add (struct eap_sim_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sha1_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ *) ; 
 size_t wpabuf_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eap_aka_add_checkcode(struct eap_aka_data *data,
				  struct eap_sim_msg *msg)
{
	const u8 *addr;
	size_t len;
	u8 hash[SHA256_MAC_LEN];

	wpa_printf(MSG_DEBUG, "   AT_CHECKCODE");

	if (data->id_msgs == NULL) {
		/*
		 * No EAP-AKA/Identity packets were exchanged - send empty
		 * checkcode.
		 */
		eap_sim_msg_add(msg, EAP_SIM_AT_CHECKCODE, 0, NULL, 0);
		return;
	}

	/* Checkcode is SHA1 hash over all EAP-AKA/Identity packets. */
	addr = wpabuf_head(data->id_msgs);
	len = wpabuf_len(data->id_msgs);
	wpa_hexdump(MSG_MSGDUMP, "EAP-AKA: AT_CHECKCODE data", addr, len);
	if (data->eap_method == EAP_TYPE_AKA_PRIME)
		sha256_vector(1, &addr, &len, hash);
	else
		sha1_vector(1, &addr, &len, hash);

	eap_sim_msg_add(msg, EAP_SIM_AT_CHECKCODE, 0, hash,
			data->eap_method == EAP_TYPE_AKA_PRIME ?
			EAP_AKA_PRIME_CHECKCODE_LEN : EAP_AKA_CHECKCODE_LEN);
}