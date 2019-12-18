#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ntlm_des_block ;
struct TYPE_4__ {int /*<<< orphan*/  nonce; } ;
struct TYPE_5__ {int lm_response_len; int /*<<< orphan*/ * lm_response; int /*<<< orphan*/  password; TYPE_1__ challenge; } ;
typedef  TYPE_2__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  des_keys_from_lm_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generate_lm_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntlm_des_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool generate_lm_response(ntlm_client *ntlm)
{
	ntlm_des_block lm_hash[2], key[3], lm_response[3];
	ntlm_des_block *challenge = (ntlm_des_block *)&ntlm->challenge.nonce;

	/* Generate the LM hash from the password */
	if (!generate_lm_hash(lm_hash, ntlm->password))
		return false;

	/* Convert that LM hash to three DES keys */
	des_keys_from_lm_hash(key, lm_hash);

	/* Finally, encrypt the challenge with each of these keys */
	if (!ntlm_des_encrypt(&lm_response[0], challenge, &key[0]) ||
		!ntlm_des_encrypt(&lm_response[1], challenge, &key[1]) ||
		!ntlm_des_encrypt(&lm_response[2], challenge, &key[2]))
		return false;

	memcpy(&ntlm->lm_response[0], lm_response[0], 8);
	memcpy(&ntlm->lm_response[8], lm_response[1], 8);
	memcpy(&ntlm->lm_response[16], lm_response[2], 8);

	ntlm->lm_response_len = sizeof(ntlm->lm_response);

	return true;
}